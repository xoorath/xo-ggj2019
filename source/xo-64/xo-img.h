#ifndef __XO_IMG_H_
#define __XO_IMG_H_

#include <PR/ultratypes.h>
#include <PR/gbi.h>

typedef struct {
  u8* start;
  u8* end;
  u32 w, h;
  u32 txSettingU, txSettingV; // G_TX_CLAMP | G_TX_NOMIRROR
  void* data;
  Vtx* mesh;
} ImgSeg_t;

typedef struct {
  u16 componentCount;
  ImgSeg_t* components;

  // f32 chosen here because it will typically be used with layout code.
  // components on the other hand use w/h for buffer sizes, so they're unsigned ints.
  f32 w, h;

  u32 filter; // G_TF_POINT | G_TF_BILERP
} Img_t;

// global init, call once before loading any textures.
void xo_img_init();

void xo_img_Load(Img_t *img);
void xo_img_Unload(Img_t *img);

void xo_img_Bind(Img_t *img, u8 segment);
void xo_img_Unbind(void);
void xo_img_Apply(Img_t *img, u8 segment);

#endif