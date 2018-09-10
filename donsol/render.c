/*
   graphic.c

   The general graphic routine (the initialization and clear the frame 
   buffer) and the definition of the external variable 

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <assert.h>
#include <nusys.h>
#include "render.h"

#define GFX_GLIST_LEN 2048

static RenderFrameData_t g_RenderFrameDatas[2];
// internal
static Gfx g_GfxList[2][GFX_GLIST_LEN];

static u32 g_TaskIdx = 0;

static Vp g_Vp = {
    SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* The scale factor  */
    SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* Move  */
};

static Gfx g_Rdpstate[] = {
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
    gsDPSetColorDither(G_CD_BAYER),
    gsSPEndDisplayList(),
};

static Gfx g_Rspstate[] = {
    gsSPViewport(&g_Vp),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsSPEndDisplayList(),
};

//////////////////////////////////////////////////////////////////////////////////////////

// extern
RenderState_t g_RenderState;

// extern
RenderFrameData_t *g_RenderFrameData = &g_RenderFrameDatas[0];

// extern
Gfx *g_Gfx = NULL;

// extern
CycleInfo_t g_DefaultCycleInfo = {
    .cycleType = G_CYC_1CYCLE,
    .cycle1Mode = G_RM_AA_OPA_SURF,
    .cycle2Mode = G_RM_AA_OPA_SURF2};

//////////////////////////////////////////////////////////////////////////////////////////

static void Render_InitDisplayList(void)
{
  gSPSegment(GFX(), 0, 0x0);
  gSPDisplayList(GFX(), OS_K0_TO_PHYSICAL(g_Rspstate));
  gSPDisplayList(GFX(), OS_K0_TO_PHYSICAL(g_Rdpstate));
}

static void Render_Clear(void)
{
  /* Clear the Z-buffer  */
  gDPSetDepthImage(GFX(), OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetCycleType(GFX(), G_CYC_FILL);
  gDPSetColorImage(GFX(), G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetFillColor(GFX(), (GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)));
  gDPFillRectangle(GFX(), 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
  gDPPipeSync(GFX());

  /* Clear the frame buffer  */
  gDPSetColorImage(GFX(), G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, osVirtualToPhysical(nuGfxCfb_ptr));
  gDPSetFillColor(GFX(), (GPACK_RGBA5551(0, 0, 0, 1) << 16 | GPACK_RGBA5551(0, 0, 0, 1)));
  gDPFillRectangle(GFX(), 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
  gDPPipeSync(GFX());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// extern
void Render_Mesh(Mesh_t *mesh)
{
  u16 i, *id;
  gSPVertex(GFX(), mesh->vtx, mesh->vtxCount, 0);
  gDPPipeSync(GFX());
  id = mesh->idx;
  for (i = 0; i < mesh->idxCount; i += 6)
  {
    // http://level42.ca/projects/ultra64/Documentation/man/n64man/gsp/gSP2Triangles.html
    gSP2Triangles(GFX(),
                  id[0 + i], id[1 + i], id[2 + i],
                  0,
                  id[3 + i], id[4 + i], id[5 + i],
                  0);
  }
  for (; i < mesh->idxCount; i += 3)
  {
    // http://level42.ca/projects/ultra64/Documentation/man/n64man/gsp/gSP2Triangles.html
    gSP1Triangle(GFX(),
                 id[0 + i], id[1 + i], id[2 + i],
                 0);
  }
}

// extern
void Render_BeginFrame(void)
{
  g_RenderFrameData = &g_RenderFrameDatas[g_TaskIdx];
  g_Gfx = &g_GfxList[g_TaskIdx][0];
  Render_Clear();

  guOrtho(&g_RenderFrameData->projection,
          -(float)SCREEN_WD / 2.0F, (float)SCREEN_WD / 2.0F,
          -(float)SCREEN_HT / 2.0F, (float)SCREEN_HT / 2.0F,
          1.0F, 10.0F, 1.0F);
  gSPMatrix(GFX(), OS_K0_TO_PHYSICAL(&(g_RenderFrameData->projection)), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
}

// extern
void Render_EndFrame(void)
{
  g_TaskIdx ^= 1;
}

// extern
void Render_BeginDraw(void)
{
  Render_InitDisplayList();

  gSPMatrix(GFX(), OS_K0_TO_PHYSICAL(&(g_RenderFrameData->translation)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
  gSPMatrix(GFX(), OS_K0_TO_PHYSICAL(&(g_RenderFrameData->rotation)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  gDPPipeSync(GFX());
}

// extern
void Render_EndDraw(void)
{
  // todo: does this have to happen just once per frame? http://n64.icequake.net/doc/n64intro/kantan/step3/index9.html
  gDPFullSync(GFX());
  gSPEndDisplayList(GFX());

#ifdef DNU_DEBUG
  assert((g_Gfx - g_GfxList[g_TaskIdx]) < GFX_GLIST_LEN);
#endif

  nuGfxTaskStart(&g_GfxList[g_TaskIdx][0],
                 (s32)(g_Gfx - g_GfxList[g_TaskIdx]) * sizeof(Gfx),
                 NU_GFX_UCODE_F3DEX,
                 NU_SC_NOSWAPBUFFER);

  gSPPopMatrix(GFX(), G_MTX_MODELVIEW);

  g_RenderFrameData = &g_RenderFrameDatas[g_TaskIdx];
  g_Gfx = &g_GfxList[g_TaskIdx][0];
}

// extern
void Render_SetGeometryMode(GeometryMode_t geometryMode)
{
  gSPClearGeometryMode(GFX(), 0xFFFFFFFF);
  gSPSetGeometryMode(GFX(), geometryMode);
}

void Render_SetCycleInfo(CycleInfo_t *cycleInfo)
{
  gDPSetCycleType(GFX(), cycleInfo->cycleType);
  gDPSetRenderMode(GFX(), cycleInfo->cycle1Mode, cycleInfo->cycle2Mode);
}