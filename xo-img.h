#ifndef __XO_IMG_H_
#define __XO_IMG_H_

#include <PR/ultratypes.h>

typedef struct {
  u8* start;
  u8* end;
} ImgSeg_t;

typedef struct {
  u16 componentCount;
  ImgSeg_t* components;
} Img_t;

extern Img_t img_donsol_heart_ace;

// Use this texture for any rendering that follows
void xo_img_Bind(Img_t *img);
void xo_img_Bind2(Img_t *img);

#endif