#ifndef __XO_IMG_H_
#define __XO_IMG_H_

#include <PR/ultratypes.h>

typedef struct {
  u8* start;
  u8* end;
  u32 w, h;
  u32 txSettingU, txSettingV; // G_TX_CLAMP | G_TX_NOMIRROR
} ImgSeg_t;

typedef struct {
  u16 componentCount;
  ImgSeg_t* components;

  u32 filter; // G_TF_POINT | G_TF_BILERP
} Img_t;

void xo_img_Bind(Img_t *img, u8 segment);
void xo_img_Unbind(void);
void xo_img_Apply(Img_t *img, u8 segment);

#endif