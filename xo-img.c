#include "xo-img.h"
#include "xo-render.h"

#include "img-donsol-heart-ace.h"

u8 img_buff[8200];

void Img2Ram(void *from_addr, void *to_addr, s32 seq_size)
{
  nuPiReadRom((u32)from_addr, to_addr, seq_size);
}

ImgSeg_t heart_ace_components[] = {
  {
    _heartaceSegmentRomStart,
    _heartaceSegmentRomEnd
  }
};

Img_t img_donsol_heart_ace = {
  sizeof(heart_ace_components)/sizeof(heart_ace_components[0]),
  heart_ace_components
};

void xo_img_Bind(Img_t *img)
{
  if(img) {
    Img2Ram(img->components[0].start, img_buff, img->components[0].end - img->components[0].start);
  }

  //gSPClearGeometryMode(g_Glist++,0xFFFFFFFF);
  //gSPSetGeometryMode(g_Glist++, G_LIGHTING | G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH |
    //     G_CULL_BACK);

  gDPSetRenderMode(g_Glist++,G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
  gDPSetColorDither(g_Glist++,G_CD_DISABLE);
#ifndef __INTELLISENSE__
  gDPSetCombineMode(g_Glist++, G_CC_DECALRGBA, G_CC_DECALRGBA);
#endif

  gDPSetTexturePersp (g_Glist++,G_TP_PERSP);
  gDPSetTextureLOD (g_Glist++,G_TL_TILE);
  gDPSetTextureFilter (g_Glist++,G_TF_BILERP);
  gDPSetTextureConvert(g_Glist++,G_TC_FILT);
  gDPSetTextureLUT (g_Glist++,G_TT_NONE);
  gSPTexture(g_Glist++,0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);


}

void xo_img_Bind2(Img_t* img)
{
    gDPLoadTextureBlock(g_Glist++,
    &img_buff[4],
    G_IM_FMT_RGBA,
    G_IM_SIZ_16b,
    32, 32, 0,
    G_TX_WRAP | G_TX_MIRROR,
    G_TX_WRAP | G_TX_MIRROR,
    4, 4,
    G_TX_NOLOD, G_TX_NOLOD);
}