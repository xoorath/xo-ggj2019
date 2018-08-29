#include <assert.h>
#include <nusys.h>
#include "render.h"

static RenderState_t g_RenderStates[2];

static MeshSettings_t g_DefaultMeshSettings = {
  .cycleType    = G_CYC_1CYCLE,
  .renderMode0  = G_RM_AA_OPA_SURF,
  .renderMode1  = G_RM_AA_OPA_SURF2,
  .geometryMode = G_SHADE| G_SHADING_SMOOTH
};

// extern
Gfx gfx_glist[2][GFX_GLIST_LEN];
// extern
RenderState_t* g_RenderState = &g_RenderStates[0];
// extern
Gfx *g_Gfx;
// extern
u32 g_RenderFrameIdx = 0;

static Vp vp = {
    SCREEN_WD * 2,
    SCREEN_HT * 2,
    G_MAXZ / 2,
    0,
    SCREEN_WD * 2,
    SCREEN_HT * 2,
    G_MAXZ / 2,
    0,
};

static Gfx setup_rdpstate[] = {
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
    gsDPSetColorDither(G_CD_BAYER),
    gsSPEndDisplayList(),
};

static Gfx setup_rspstate[] = {
    gsSPViewport(&vp),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsSPEndDisplayList(),
};

// INTERNAL
static const unsigned int z_black = (GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0));
static const unsigned int c_black = (GPACK_RGBA5551(0, 0, 0, 1) << 16 | GPACK_RGBA5551(0, 0, 0, 1));
static void Render_Clear(void)
{
  // clear z-buffer
  gDPSetDepthImage( GFX(), OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetCycleType(  GFX(), G_CYC_FILL);
  gDPSetColorImage( GFX(), G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetFillColor(  GFX(), z_black);
  gDPFillRectangle( GFX(), 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
  gDPPipeSync(GFX());

  // clear color
  gDPSetColorImage( GFX(), G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, osVirtualToPhysical(nuGfxCfb_ptr));
  gDPSetFillColor(  GFX(), c_black);
  gDPFillRectangle( GFX(), 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
  gDPPipeSync(GFX());
}

//////////////////////////////////////////////////////////////////////////////////////////

//extern
void Render_MeshDefault(Mesh_t* mesh) {
  Render_Mesh(mesh, &g_DefaultMeshSettings);
}

// extern
void Render_Mesh(Mesh_t* mesh, MeshSettings_t* settings) {
  u16 firstPassTriangleCount, i;

#ifdef DNU_DEBUG
  assert(mesh->idxCount % 6 == 0);
#endif

  gSPVertex(GFX(),mesh->vtx,mesh->vtxCount, 0);

  gDPPipeSync(GFX());
  gDPSetCycleType(GFX(),settings->cycleType);
  gDPSetRenderMode(GFX(),settings->renderMode0, settings->renderMode1);
  gSPClearGeometryMode(GFX(),0xFFFFFFFF);
  gSPSetGeometryMode(GFX(),settings->geometryMode);

  if(mesh->idxCount >= 6) {
    firstPassTriangleCount = mesh->idxCount & ~(u16)1;
    for(i = 0; i < firstPassTriangleCount; i+=6) {
      gSP2Triangles(GFX(),
        mesh->idx[0+i],mesh->idx[1+i],mesh->idx[2+i],
        0,
        mesh->idx[3+i],mesh->idx[4+i],mesh->idx[5+i],
        0);
    }
  }
  if(mesh->idxCount & 1) {
    gSPTriangle(GFX(),
        mesh->idx[0+i],mesh->idx[1+i],mesh->idx[2+i], 0);
  }


}

// extern
void Render_BeginFrame(void) {
  /* Specify the display list buffer */
  g_RenderState = &g_RenderStates[g_RenderFrameIdx];
  g_Gfx = &gfx_glist[g_RenderFrameIdx][0];

  Render_Clear();

  gSPSegment(GFX(), 0, 0x0);
  gSPDisplayList(GFX(), OS_K0_TO_PHYSICAL(setup_rspstate));
  gSPDisplayList(GFX(), OS_K0_TO_PHYSICAL(setup_rdpstate));

  gSPMatrix(
    GFX(),
    OS_K0_TO_PHYSICAL(&(g_RenderState->projection)), 
    G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
}

// extern
void Render_EndFrame(void) {
  g_RenderFrameIdx ^= g_RenderFrameIdx;
}

// extern
void Render_BeginDraw(void) {
  gSPMatrix(
    GFX(),
    OS_K0_TO_PHYSICAL(&(g_RenderState->translate)), 
    G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_PUSH);

  gSPMatrix(
    GFX(),
    OS_K0_TO_PHYSICAL(&(g_RenderState->modeling)),
    G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

}

// extern
void Render_EndDraw(void) {
  gSPPopMatrix(GFX(), G_MTX_MODELVIEW);

  gDPFullSync(GFX());
  gSPEndDisplayList(GFX());
  GFX_CHECK();
  nuGfxTaskStart(
    &gfx_glist[g_RenderFrameIdx][0],
    (s32)(g_Gfx - gfx_glist[g_RenderFrameIdx]) * sizeof (Gfx),
    NU_GFX_UCODE_F3DEX , NU_SC_NOSWAPBUFFER);
}