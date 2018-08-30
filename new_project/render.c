/*
   graphic.c

   The general graphic routine (the initialization and clear the frame 
   buffer) and the definition of the external variable 

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <assert.h>
#include <nusys.h>
#include "render.h"

static RenderData_t gfx_dynamic[2];

Gfx          gfx_glist[2][GFX_GLIST_LEN];
Gfx          gfx_clear_glist[2][GFX_CLEAR_GLIST_LEN];
RenderData_t* g_RenderData = &gfx_dynamic[0];
Gfx*         glistp;
u32          gfx_gtask_no = 0;

static 
Vp vp = {
    SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* The scale factor  */
    SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* Move  */
};

static 
Gfx setup_rdpstate[] = {
  gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
  gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
  gsDPSetScissor(G_SC_NON_INTERLACE, 0,0, SCREEN_WD,SCREEN_HT),
  gsDPSetColorDither(G_CD_BAYER),
  gsSPEndDisplayList(),
};

static 
Gfx setup_rspstate[] = {
  gsSPViewport(&vp),
  gsSPClearGeometryMode(0xFFFFFFFF),
  gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK),
  gsSPTexture(0, 0, 0, 0, G_OFF),
  gsSPEndDisplayList(),
};

static 
void gfxRCPInit(void)
{
  gSPSegment(glistp++, 0, 0x0);
  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(setup_rspstate));
  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(setup_rdpstate));
}

static 
void gfxClearCfb(void)
{
  /* Clear the Z-buffer  */
  gDPSetDepthImage(glistp++, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetCycleType(glistp++, G_CYC_FILL);
  gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b,SCREEN_WD, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetFillColor(glistp++,(GPACK_ZDZ(G_MAXFBZ,0) << 16 | GPACK_ZDZ(G_MAXFBZ,0)));
  gDPFillRectangle(glistp++, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
  gDPPipeSync(glistp++);
  
    /* Clear the frame buffer  */
  gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, osVirtualToPhysical(nuGfxCfb_ptr));
  gDPSetFillColor(glistp++, (GPACK_RGBA5551(0, 0, 0, 1) << 16 | GPACK_RGBA5551(0, 0, 0, 1)));
  gDPFillRectangle(glistp++, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
  gDPPipeSync(glistp++);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// extern
void Render_BeginFrame(void) {
  g_RenderData = &gfx_dynamic[gfx_gtask_no];
  glistp = &gfx_glist[gfx_gtask_no][0];
  gfxClearCfb();

  guOrtho(&g_RenderData->projection,
      -(float)SCREEN_WD/2.0F, (float)SCREEN_WD/2.0F,
      -(float)SCREEN_HT/2.0F, (float)SCREEN_HT/2.0F,
      1.0F, 10.0F, 1.0F);
}


// extern
void Render_EndFrame(void) {
  gfx_gtask_no ^= 1;
}

// extern
void Render_BeginDraw(void) {
  gfxRCPInit();

  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(g_RenderData->projection)), G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(g_RenderData->translate)),G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(g_RenderData->modeling)), G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
  gDPPipeSync(glistp++);

  gDPSetCycleType(glistp++,G_CYC_1CYCLE);
  gDPSetRenderMode(glistp++,G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
  gSPClearGeometryMode(glistp++,0xFFFFFFFF);
  gSPSetGeometryMode(glistp++,G_SHADE| G_SHADING_SMOOTH);
}

// extern
void Render_EndDraw(void) {
  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);

  nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0], (s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof (Gfx), NU_GFX_UCODE_F3DEX , NU_SC_NOSWAPBUFFER);

  gSPPopMatrix(glistp++, G_MTX_MODELVIEW);

  g_RenderData = &gfx_dynamic[gfx_gtask_no];
  glistp = &gfx_glist[gfx_gtask_no][0];
}
