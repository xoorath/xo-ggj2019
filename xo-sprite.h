#ifndef __XO_SPRITE_H_
#define __XO_SPRITE_H_

#include "xo-img.h"
#include "xo-render.h"

typedef struct {
  Transformation_t parent, xform;
  Img_t* img;
  f32 x, y, z, r;
} Sprite_t;

void xo_sprite_init(Sprite_t* sprite, Img_t* img);

// draw at a sprites x, y relative to some position on the sprite.
void xo_sprite_draw_center(Sprite_t* sprite);
void xo_sprite_draw_bottom_left(Sprite_t* sprite);
void xo_sprite_draw_top_left(Sprite_t* sprite);
void xo_sprite_draw_top_right(Sprite_t* sprite);
void xo_sprite_draw_bottom_right(Sprite_t* sprite);

#endif