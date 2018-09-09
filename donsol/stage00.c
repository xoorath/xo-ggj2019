/*
   stage00.c 

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.	
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "render.h"

#include "gen.n6401.h"

static float triPos_x; /* The display position, X */
static float triPos_y; /* The display position, Y */
static float theta;  /* The rotational angle of the square  */

/* The vertex coordinate  */

#define VTX_POS(x, y, z) x, y, z
#define VTX_UV(u, v) u, v
#define VTX_RGBA(r, g, b, a) r, g, b, a
static Vtx shade_vtx[] =  {
        {VTX_POS(-64,  64, -5), 0, VTX_UV(0,    2048),   VTX_RGBA(0xff, 0xff, 0xff, 0xff) },
        {VTX_POS( 64,  64, -5), 0, VTX_UV(2048, 2048),   VTX_RGBA(0xff, 0xff, 0xff, 0xff) },
        {VTX_POS( 64, -64, -5), 0, VTX_UV(2048, 0   ),   VTX_RGBA(0xff, 0xff, 0xff, 0xff) },
        {VTX_POS(-64, -64, -5), 0, VTX_UV(0,    0   ),   VTX_RGBA(0xff, 0xff, 0xff, 0xff) },
};
#undef VTX_POS
#undef VTX_UV
#undef VTX_RGBA

static u16 squareIndicies[] = {0,1,2, 2,3,0};

static Mesh_t squareMesh = {
  .vtx = shade_vtx,
  .vtxCount = sizeof(shade_vtx)/sizeof(*shade_vtx),
  .idx = squareIndicies,
  .idxCount = sizeof(squareIndicies)/sizeof(*squareIndicies)
};

extern u8 _gentexSegmentRomStart[];
extern u8 _gentexSegmentRomEnd[];

void DrawTexture();
//void ReadTexture();
/* The initialization of stage 0  */
void initStage00(void)
{
  triPos_x = 0.0;
  triPos_y = 0.0;
  theta = 0.0;
  //ReadTexture();
  
}

/* Make the display list and activate the task  */
void makeDL00(void)
{
  { Render_BeginFrame(); 
  
    guTranslate(&g_RenderFrameData->translation, triPos_x, triPos_y, 0.0F);
    guRotate(&g_RenderFrameData->rotation, theta, 0.0F, 0.0F, 1.0F);

//    { Render_BeginDraw();
//      Render_SetCycleInfo(&g_DefaultCycleInfo);
//      Render_SetGeometryMode(G_SHADE | G_SHADING_SMOOTH);
//      Render_Mesh(&squareMesh);
//    } Render_EndDraw();

    guTranslate(&g_RenderFrameData->translation, triPos_x, triPos_y, 0.0F);
    guRotate(&g_RenderFrameData->rotation, 0.f, 0.0F, 0.0F, 1.0F);
    
    { Render_BeginDraw();
      Render_SetCycleInfo(&g_DefaultCycleInfo);
      Render_SetGeometryMode(G_SHADE | G_SHADING_SMOOTH);
      DrawTexture();
      Render_Mesh(&squareMesh);
    } Render_EndDraw();

  } Render_EndFrame();
}

// unsigned short MovieBuf[8200];

// void ReadTexture()
// {

//     u32 r2rlen;
//     u32 onecutlen;

//     /* Compute the stored segment heads of the movie data */
//     r2rlen = _gentexSegmentRomEnd - _gentexSegmentRomStart;

//     /* Compute the length of each scene */
//     onecutlen = r2rlen;

//     /* Copy data from ROM to RDRAM, practically */
//     nuPiReadRom( (u32)(_gentexSegmentRomStart + onecutlen),
// 		(void *)&(MovieBuf[0]),
// 		onecutlen
// 		);
// }
/**
 * 
 *  *   Size: 64 x 64
 *   Number of channels: 3
 *   Number of bits per texel: 16 (G_IM_SIZ_16b)
 *   Format of texel: G_IM_FMT_RGBA
 * 
 *  *   gsDPPipeSync (),
 *   gsDPSetCombineMode (G_CC_DECALRGB, G_CC_DECALRGB),
 *   gsDPSetTexturePersp (G_TP_PERSP),
 *   gsDPSetTextureLOD (G_TL_TILE),
 *   gsDPSetTextureFilter (G_TF_BILERP),
 *   gsDPSetTextureConvert(G_TC_FILT),
 *   gsDPSetTextureLUT (G_TT_NONE),
 *   gsDPLoadTextureBlock (ani01, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 64, 0,
 *     G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
 *     G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
*/
void DrawTexture() {
  gDPSetTextureFilter(GFX(), G_TF_POINT /*G_TF_BILERP*/);
  gDPSetCombineMode(GFX(), G_CC_DECALRGB, G_CC_DECALRGB);
  gDPSetTexturePersp(GFX(), G_TP_PERSP);
  gDPSetTextureLOD(GFX(), G_TL_TILE);
  gSPTexture(GFX(), 0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);
  gDPLoadTextureBlock(GFX(), ani012, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 64, 0,
    G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

}


/* The game progressing process for stage 0 */
void updateGame00(void)
{  
  static float vel = 1.0;

  /* Data reading of controller 1  */
  nuContDataGetEx(contdata,0);

  /* Change the display position according to stick data  */
  triPos_x = contdata->stick_x;
  triPos_y = contdata->stick_y;

  /* The reverse rotation by the A button  */
  if(contdata[0].trigger & A_BUTTON)
    vel = -vel;

  /* Rotate fast while the B button is pushed  */
  if(contdata[0].button & B_BUTTON)
    theta += vel * 3.0;
  else
    theta += vel;

  /* Change the pending check when the Z button is pushed  */
  if(contdata[0].trigger & Z_TRIG)
    pendflag ^= 1;
}
