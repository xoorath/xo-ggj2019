#include "xo-img.h"
#include "xo-render.h"

#include "img-donsol-heart-ace.h"
static u8 img_buff[8200];

void Rom2Ram(void *from_addr, void *to_addr, s32 seq_size);

ImgSeg_t heart_ace_components[] = {
  {
    _heartaceSegmentRomStart,
    _heartaceSegmentRomEnd,
    32, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR
  }
};

Img_t img_donsol_heart_ace = {
  sizeof(heart_ace_components)/sizeof(heart_ace_components[0]),
  heart_ace_components,

  G_TF_POINT
};

void xo_img_Bind(Img_t *img, u8 segment)
{
  ImgSeg_t* seg;
  if(img) {
    seg = &img->components[segment];
    Rom2Ram(seg->start, img_buff, seg->end - seg->start);

    gDPSetColorDither(g_Glist++,G_CD_ENABLE);
    //gDPSetTexturePersp(g_Glist++,G_TP_PERSP);
    //gDPSetTextureLOD(g_Glist++,G_TL_TILE);
    //gDPSetTextureConvert(g_Glist++,G_TC_FILT);
    //gDPSetTextureLUT(g_Glist++,G_TT_NONE);

#ifndef __INTELLISENSE__
    gDPSetCombineMode(g_Glist++, G_CC_DECALRGBA, G_CC_DECALRGBA);
#endif
    gDPSetTextureFilter(g_Glist++, img->filter);
    gSPTexture(g_Glist++,0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
  } else {
    xo_img_Unbind();
  }
}

void xo_img_Unbind(void)
{
#ifndef __INTELLISENSE__
  gDPSetCombineMode(g_Glist++, G_CC_SHADE, G_CC_SHADE);
#endif
  gSPTexture(g_Glist++,0, 0, 0, 0, G_OFF);
}

void xo_img_Apply(Img_t* img, u8 segment)
{
  ImgSeg_t* seg = &img->components[segment];
  gDPLoadTextureBlock(g_Glist++,
    &img_buff[8],
    G_IM_FMT_RGBA,
    G_IM_SIZ_16b,
    seg->w, seg->h, 0,
    seg->txSettingU,
    seg->txSettingV,
    5, 5,
    G_TX_NOLOD, G_TX_NOLOD);
}