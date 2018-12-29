#include "xo-img.h"
#include "xo-render.h"

#include "img-donsol-heart-ace.h"
static u8 img_buff[8200];

void Rom2Ram(void *from_addr, void *to_addr, s32 seq_size);

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
    Rom2Ram(img->components[0].start, img_buff, img->components[0].end - img->components[0].start);
    //gDPSetColorDither(g_Glist++,G_CD_DISABLE);
    //gDPSetTexturePersp(g_Glist++,G_TP_PERSP);
    //gDPSetTextureLOD(g_Glist++,G_TL_TILE);
    //gDPSetTextureConvert(g_Glist++,G_TC_FILT);
    //gDPSetTextureLUT(g_Glist++,G_TT_NONE);

#ifndef __INTELLISENSE__
    gDPSetCombineMode(g_Glist++, G_CC_DECALRGBA, G_CC_DECALRGBA);
#endif
    gDPSetTextureFilter(g_Glist++,1?G_TF_POINT:G_TF_BILERP);
    gSPTexture(g_Glist++,0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
  } else {
#ifndef __INTELLISENSE__
    gDPSetCombineMode(g_Glist++, G_CC_SHADE, G_CC_SHADE);
#endif
    gSPTexture(g_Glist++,0, 0, 0, 0, G_OFF);
  }
}

void xo_img_Bind2(Img_t* img)
{
  gDPLoadTextureBlock(g_Glist++,
    &img_buff[8],
    G_IM_FMT_RGBA,
    G_IM_SIZ_16b,
    32, 32, 0,
    G_TX_CLAMP | G_TX_NOMIRROR,
    G_TX_CLAMP | G_TX_NOMIRROR,
    5, 5,
    G_TX_NOLOD, G_TX_NOLOD);
}