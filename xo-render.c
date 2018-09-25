#include "xo-render.h"
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#define GLIST_RENDER_LENGTH 2048
#define GLIST_CLEAR_LENGTH 512

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

static u32 s_ClearColor;
static Gfx s_GlistClear[2][GLIST_CLEAR_LENGTH];
static Gfx s_GlistRender[2][GLIST_RENDER_LENGTH];
static s32 s_DebugLineNum = 1;
static u32 s_TaskNumber = 0;
static FrameData_t s_FrameDataCollection[2];
static Mtx s_RootTransformation;

Gfx *g_Glist;
FrameData_t *g_FrameData = NULL;

static void xo_render_InitRCP(void)
{
  // Setting the RSP segment register
  gSPSegment(g_Glist++, 0, 0x0);
  // setup reality signal processor state
  gSPDisplayList(g_Glist++, OS_K0_TO_PHYSICAL(setup_rspstate));
  // setup reality display processor state
  gSPDisplayList(g_Glist++, OS_K0_TO_PHYSICAL(setup_rdpstate));
}

static void xo_render_Clear(void)
{
  gDPSetDepthImage(g_Glist++, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetCycleType(g_Glist++, G_CYC_FILL);
  gDPSetColorImage(g_Glist++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetFillColor(g_Glist++, (GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)));
  gDPFillRectangle(g_Glist++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
  gDPPipeSync(g_Glist++);

  gDPSetColorImage(g_Glist++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, osVirtualToPhysical(nuGfxCfb_ptr));
  gDPSetFillColor(g_Glist++, s_ClearColor);
  gDPFillRectangle(g_Glist++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
  gDPPipeSync(g_Glist++);
}

static void xo_render_BeginDisplayList_Clear(void)
{
  g_Glist = &s_GlistClear[s_TaskNumber][0];
  xo_render_InitRCP();
}

static void xo_render_EndDisplayList_Clear(void)
{
  // this can fail on overflow or when using the wrong Glist
#ifdef DNU_DEBUG
  assert(g_Glist > (Gfx*)&s_GlistClear[0] && g_Glist < (Gfx*)&s_GlistClear[GLIST_CLEAR_LENGTH]);
#endif

  gDPFullSync(g_Glist++);
  gSPEndDisplayList(g_Glist++);

  nuGfxTaskStart(&(s_GlistClear[s_TaskNumber][0]),
                 (s32)(g_Glist - (s_GlistClear[s_TaskNumber])) * sizeof(Gfx),
                 NU_GFX_UCODE_F3DEX, NU_SC_NOSWAPBUFFER);
}

//////////////////////////////////////////////////////////////////////////////////////////

void xo_render_Init(void)
{
  guMtxIdent(&s_RootTransformation);
  xo_render_SetClearColor(100, 149, 237);
}

void xo_render_BeginFrame(void)
{
  g_FrameData = &s_FrameDataCollection[s_TaskNumber];
  xo_render_BeginDisplayList_Clear();
  xo_render_Clear();
  xo_render_EndDisplayList_Clear();
}

void xo_render_EndFrame(void)
{
  xo_render_DebugDraw();
  s_TaskNumber ^= 1;
}

void xo_render_BeginDisplayList_Render(void)
{
  g_Glist = &s_GlistRender[s_TaskNumber][0];
  xo_render_InitRCP();

  guOrtho(&g_FrameData->projection,
          -(f32)SCREEN_WD / 2.0F, (f32)SCREEN_WD / 2.0F,
          -(f32)SCREEN_HT / 2.0F, (f32)SCREEN_HT / 2.0F,
          1.0F, 10.0F, 1.0F);

  gSPMatrix(g_Glist++, OS_K0_TO_PHYSICAL(&g_FrameData->projection),
            G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

  gSPMatrix(g_Glist++, OS_K0_TO_PHYSICAL(&s_RootTransformation),
            G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_PUSH);
}

void xo_render_EndDisplayList_Render(void)
{
  gSPPopMatrix(g_Glist++, G_MTX_MODELVIEW); // pop root transform

  // this can fail on overflow or when using the wrong Glist
  assert(g_Glist > &s_GlistRender[0] && g_Glist < &s_GlistRender[GLIST_RENDER_LENGTH]);

  gDPFullSync(g_Glist++);
  gSPEndDisplayList(g_Glist++);

  nuGfxTaskStart(&(s_GlistRender[s_TaskNumber][0]),
                 (s32)(g_Glist - (s_GlistRender[s_TaskNumber])) * sizeof(Gfx),
                 NU_GFX_UCODE_F3DEX, NU_SC_NOSWAPBUFFER);
}

void xo_render_BeginDraw(Transformation_t *t)
{
  gSPMatrix(g_Glist++, OS_K0_TO_PHYSICAL(&t->translation), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
  gSPMatrix(g_Glist++, OS_K0_TO_PHYSICAL(&t->rotation), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
}

void xo_render_EndDraw(void)
{
  gSPPopMatrix(g_Glist++, G_MTX_MODELVIEW);
}

void xo_render_Translate(Transformation_t *t, f32 x, f32 y, f32 z)
{
  guTranslate(&t->translation, x, y, z);
}

void xo_render_Rotate(Transformation_t *t, f32 angle, f32 x, f32 y, f32 z)
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

void xo_render_SetClearColor(u8 r, u8 g, u8 b)
{
  s_ClearColor = (GPACK_RGBA5551(r, g, b, 1) << 16 | GPACK_RGBA5551(r, g, b, 1));
}