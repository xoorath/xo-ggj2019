/*
   stage00.c 

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.	
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "render.h"


static float triPos_x; /* The display position, X */
static float triPos_y; /* The display position, Y */
static float theta;    /* The rotational angle of the square  */

/* The vertex coordinate  */

#define VTX_POS(x, y, z) x, y, z
#define VTX_UV(u, v) u, v
#define VTX_RGBA(r, g, b, a) r, g, b, a
#define TEX_WRAP 5 // why 5? why does this work?
static Vtx shade_vtx_0[] = {
    {VTX_POS(-64, 64, -5),   0, VTX_UV(00 << TEX_WRAP, 00 << TEX_WRAP), VTX_RGBA(0xff, 0xff, 0xff, 0xff)},
    {VTX_POS(64,  64, -5),   0, VTX_UV(63 << TEX_WRAP, 00 << TEX_WRAP), VTX_RGBA(0xff, 0xff, 0xff, 0xff)},
    {VTX_POS(64,   0, -5),   0, VTX_UV(63 << TEX_WRAP, 31 << TEX_WRAP), VTX_RGBA(0xff, 0xff, 0xff, 0xff)},

    {VTX_POS(64,    0, -5),  0, VTX_UV(63 << TEX_WRAP, 31 << TEX_WRAP), VTX_RGBA(0xff, 0xff, 0xff, 0xff)},
    {VTX_POS(-64,   0, -5),  0, VTX_UV(00 << TEX_WRAP, 31 << TEX_WRAP), VTX_RGBA(0xff, 0xff, 0xff, 0xff)},
    {VTX_POS(-64,  64, -5),  0, VTX_UV(00 << TEX_WRAP, 00 << TEX_WRAP), VTX_RGBA(0xff, 0xff, 0xff, 0xff)}
};

static Vtx shade_vtx_1[] = {
    {VTX_POS(-64,  0, -5),   0, VTX_UV(00 << TEX_WRAP, 0 << TEX_WRAP), VTX_RGBA(0xff, 0xff, 0xff, 0xff)},
    {VTX_POS(64,   0, -5),   0, VTX_UV(63 << TEX_WRAP, 0 << TEX_WRAP), VTX_RGBA(0xff, 0xff, 0xff, 0xff)},
    {VTX_POS(64, -64, -5),   0, VTX_UV(63 << TEX_WRAP, 31 << TEX_WRAP), VTX_RGBA(0xff, 0xff, 0xff, 0xff)},

    {VTX_POS(64,  -64, -5),  0, VTX_UV(63 << TEX_WRAP, 31 << TEX_WRAP), VTX_RGBA(0xff, 0xff, 0xff, 0xff)},
    {VTX_POS(-64, -64, -5),  0, VTX_UV(00 << TEX_WRAP, 31 << TEX_WRAP), VTX_RGBA(0xff, 0xff, 0xff, 0xff)},
    {VTX_POS(-64,   0, -5),  0, VTX_UV(00 << TEX_WRAP, 0 << TEX_WRAP), VTX_RGBA(0xff, 0xff, 0xff, 0xff)}
};
#undef VTX_POS
#undef VTX_UV
#undef VTX_RGBA
#undef TEX_WRAP

static u16 squareIndicies_0[] = {0, 1, 2, 3, 4, 5};
static u16 squareIndicies_1[] = {6, 7, 8, 9, 10, 11};

static Mesh_t squareMesh_0 = {
    .vtx = shade_vtx_0,
    .vtxCount = 6,
    .idx = squareIndicies_0,
    .idxCount = sizeof(squareIndicies_0) / sizeof(*squareIndicies_0)};

static Mesh_t squareMesh_1 = {
    .vtx = shade_vtx_1,
    .vtxCount = 6,
    .idx = squareIndicies_0,
    .idxCount = sizeof(squareIndicies_0) / sizeof(*squareIndicies_0)};

extern u8 _gentexSegmentRomStart[];
extern u8 _gentexSegmentRomEnd[];

void DrawTexture(int i);
void ReadTexture();
/* The initialization of stage 0  */
void initStage00(void)
{
  triPos_x = 0.0;
  triPos_y = 0.0;
  theta = 0.0;
  ReadTexture();
}

/* Make the display list and activate the task  */
void makeDL00(void)
{
  {
    Render_BeginFrame();

    //guTranslate(&g_RenderFrameData->translation, triPos_x, triPos_y, 0.0F);
    //guRotate(&g_RenderFrameData->rotation, theta, 0.0F, 0.0F, 1.0F);

    //{ Render_BeginDraw();
    //  Render_SetCycleInfo(&g_DefaultCycleInfo);
    //  Render_SetGeometryMode(G_SHADE | G_SHADING_SMOOTH);
    //  Render_Mesh(&squareMesh_0);
    //} Render_EndDraw();

    guTranslate(&g_RenderFrameData->translation, triPos_x, triPos_y, 0.0F);
    guRotate(&g_RenderFrameData->rotation, 0.f, 0.0F, 0.0F, 1.0F);
    {
      Render_BeginDraw();
      Render_SetCycleInfo(&g_DefaultCycleInfo);
      Render_SetGeometryMode(G_TEXTURE_ENABLE | G_SHADE | G_SHADING_SMOOTH);

      {
        gDPSetTextureFilter(GFX(), G_TF_POINT /*G_TF_BILERP*/);
        gDPSetCombineMode(GFX(), G_CC_DECALRGBA, G_CC_DECALRGBA);
        gDPSetTexturePersp(GFX(), G_TP_PERSP);
        gDPSetTextureLOD(GFX(), G_TL_TILE);
        //gsDPTextureLUT(GFX(), G_TT_RGBA16);
        gDPSetTextureConvert(GFX(), G_TC_FILT);
        gDPSetCycleType(GFX(), G_CYC_1CYCLE);
        gDPSetRenderMode(GFX(),G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPTexture(GFX(), 0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);
      }
      DrawTexture(0);
      Render_Mesh(&squareMesh_0);
      DrawTexture(1);
      Render_Mesh(&squareMesh_1);

      Render_EndDraw();
    }
    Render_EndFrame();
  }
}

unsigned short MovieBuf[4 + (64 * 64)];

void ReadTexture()
{

  u32 r2rlen;
  u32 offset = 4;

  r2rlen = (u32)_gentexSegmentRomEnd - (u32)_gentexSegmentRomStart;

  nuPiReadRom((u32)(_gentexSegmentRomStart),
              (void *)MovieBuf,
              r2rlen);
}

void DrawTexture(int i)
{
  if(i == 0) {
  gDPLoadTextureBlock(GFX(),
                      &MovieBuf[4],
                      G_IM_FMT_RGBA,
                      G_IM_SIZ_16b,
                      64, 32,
                      0,
                      G_TX_WRAP, G_TX_WRAP,
                      G_TX_NOMASK, G_TX_NOMASK,
                      G_TX_NOLOD, G_TX_NOLOD);
  }
  else {
      gDPLoadTextureBlock(GFX(),
                      &MovieBuf[4 + ((32*64))],
                      G_IM_FMT_RGBA,
                      G_IM_SIZ_16b,
                      64, 32,
                      0,
                      G_TX_WRAP, G_TX_WRAP,
                      G_TX_NOMASK, G_TX_NOMASK,
                      G_TX_NOLOD, G_TX_NOLOD);
  }
  // if(i == 0) {
  // gDPLoadTextureTile(GFX(),
  //                     &MovieBuf[4],
  //                     G_IM_FMT_RGBA,
  //                     G_IM_SIZ_16b,
  //                     64, 64,
  //                     0, 0, 64, 64,
  //                     0,
  //                     G_TX_WRAP, G_TX_WRAP,
  //                     G_TX_NOMASK, G_TX_NOMASK,
  //                     G_TX_NOLOD, G_TX_NOLOD);
  // } else {
  // gDPLoadTextureTile(GFX(),
  //                     &MovieBuf[4 + (32*64*2)],
  //                     G_IM_FMT_RGBA,
  //                     G_IM_SIZ_16b,
  //                     64, 64,
  //                     32, 0, 64, 64,
  //                     0,
  //                     G_TX_WRAP, G_TX_WRAP,
  //                     G_TX_NOMASK, G_TX_NOMASK,
  //                     G_TX_NOLOD, G_TX_NOLOD);
  // }
}

/* The game progressing process for stage 0 */
void updateGame00(void)
{
  static float vel = 1.0;

  /* Data reading of controller 1  */
  nuContDataGetEx(contdata, 0);

  /* Change the display position according to stick data  */
  triPos_x = contdata->stick_x;
  triPos_y = contdata->stick_y;

  /* The reverse rotation by the A button  */
  if (contdata[0].trigger & A_BUTTON)
    vel = -vel;

  /* Rotate fast while the B button is pushed  */
  if (contdata[0].button & B_BUTTON)
    theta += vel * 3.0;
  else
    theta += vel;

  /* Change the pending check when the Z button is pushed  */
  if (contdata[0].trigger & Z_TRIG)
    pendflag ^= 1;
}
