#include "xo-render.h"
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

static Vp vp = {
    SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* The scale factor  */
    SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* Move  */
};

Gfx setup_rdpstate[] = {
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
    gsDPSetColorDither(G_CD_BAYER),
    gsSPEndDisplayList(),
};

Gfx setup_rspstate[] = {
    gsSPViewport(&vp),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsSPEndDisplayList(),
};

extern Gfx *glistp;
extern Gfx gfx_glist[][GFX_GLIST_LEN];
extern Gfx gfx_clear_glist[][GFX_CLEAR_GLIST_LEN];
extern u32 gfx_gtask_no;
static int s_DebugLineNum = 1;

FrameData_t g_FrameDataCollection[2];
FrameData_t *g_FrameData = NULL;
Mtx g_RootTransformation;

extern void gfxRCPInit(void);
extern void gfxClearCfb(void);

void xo_render_Init(void)
{
  guMtxIdent(&g_RootTransformation);
}

static void xo_render_InitRCP(void)
{
  // Setting the RSP segment register
  gSPSegment(glistp++, 0, 0x0);
  // setup reality signal processor state
  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(setup_rspstate));
  // setup reality display processor state
  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(setup_rdpstate));
}

///////////////////////////////////////////////////////////////////////////////////////// DL Clear
void xo_render_BeginDisplayList_Clear(void)
{
  glistp = &gfx_clear_glist[gfx_gtask_no][0];
  xo_render_InitRCP();
}

void xo_render_EndDisplayList_Clear(void)
{
  // todo: test glistp is inside clear list
  assert((glistp - gfx_clear_glist[gfx_gtask_no]) < GFX_CLEAR_GLIST_LEN);

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  nuGfxTaskStart(&(gfx_clear_glist[gfx_gtask_no][0]),
                 (s32)(glistp - (gfx_clear_glist[gfx_gtask_no])) * sizeof(Gfx),
                 NU_GFX_UCODE_F3DEX, NU_SC_NOSWAPBUFFER);
}

///////////////////////////////////////////////////////////////////////////////////////// DL Render
void xo_render_BeginDisplayList_Render(void)
{
  glistp = &gfx_glist[gfx_gtask_no][0];
  xo_render_InitRCP();

  guOrtho(&g_FrameData->projection,
          -(float)SCREEN_WD / 2.0F, (float)SCREEN_WD / 2.0F,
          -(float)SCREEN_HT / 2.0F, (float)SCREEN_HT / 2.0F,
          1.0F, 10.0F, 1.0F);

  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&g_FrameData->projection),
            G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&g_RootTransformation),
            G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_PUSH);
}

void xo_render_EndDisplayList_Render(void)
{
  gSPPopMatrix(glistp++, G_MTX_MODELVIEW); // pop root transform
  // todo: test glistp is inside render list
  assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  nuGfxTaskStart(&(gfx_glist[gfx_gtask_no][0]),
                 (s32)(glistp - (gfx_glist[gfx_gtask_no])) * sizeof(Gfx),
                 NU_GFX_UCODE_F3DEX, NU_SC_NOSWAPBUFFER);
}

/////////////////////////////////////////////////////////////////////////////////////////
void xo_render_BeginDraw(Transformation_t* t)
{
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&t->translation), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&t->rotation), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
}

void xo_render_EndDraw(void)
{
  gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
}

void xo_render_Translate(Transformation_t* t, float x, float y, float z)
{
  guTranslate(&t->translation, x, y, z);
}

void xo_render_Rotate(Transformation_t* t, float angle, float x, float y, float z)
{
  guRotate(&t->rotation, angle, x, y, z);
}

void xo_render_DebugDraw(void)
{
  nuDebConDisp(NU_SC_SWAPBUFFER);
  s_DebugLineNum = 1;
  nuDebConClear(NU_DEB_CON_WINDOW0);
}

void xo_render_DebugLog(char const *msg)
{
  nuDebConTextPos(0, 1, s_DebugLineNum++);
  nuDebConCPuts(NU_DEB_CON_WINDOW0, msg);
}

void xo_render_Clear(void)
{
  gDPSetDepthImage(glistp++, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetCycleType(glistp++, G_CYC_FILL);
  gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetFillColor(glistp++, (GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)));
  gDPFillRectangle(glistp++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
  gDPPipeSync(glistp++);

  /* Clear the frame buffer  */
  gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, osVirtualToPhysical(nuGfxCfb_ptr));
  gDPSetFillColor(glistp++, (GPACK_RGBA5551(255, 0, 0, 1) << 16 | GPACK_RGBA5551(255, 0, 0, 1)));
  gDPFillRectangle(glistp++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
  gDPPipeSync(glistp++);
}

void xo_render_BeginFrame(void)
{
  g_FrameData = &g_FrameDataCollection[gfx_gtask_no];
  xo_render_BeginDisplayList_Clear();
  xo_render_Clear();
  xo_render_EndDisplayList_Clear();
}

void xo_render_EndFrame(void)
{
  xo_render_DebugDraw();
  gfx_gtask_no ^= 1;
}
