#include "xo-sprite.h"

void xo_sprite_init(Sprite_t* sprite, Img_t* img) {
  sprite->img = img;
  sprite->x = sprite->y = sprite->r = 0.0f;
  sprite->z = -5.0f;
}

void xo_sprite_draw(Sprite_t* sprite) {
  u16 i;
  xo_render_BeginDraw(&sprite->xform);

  xo_img_Bind(sprite->img, 0);

  for(i = 0; i < sprite->img->componentCount; ++i) {
    xo_render_bind_mesh(sprite->img->components[i].mesh, 4);
    xo_img_Apply(sprite->img, i);
    xo_render_apply_mesh();
  }

  xo_img_Bind(NULL, 0);
  xo_render_EndDraw();
}

void xo_sprite_draw_center(Sprite_t* sprite) {
  xo_render_Translate(&sprite->parent, sprite->x, sprite->y, sprite->z);
  xo_render_Rotate(&sprite->parent, sprite->r, 0.0f, 0.0f, 1.0f);
  xo_render_BeginDraw(&sprite->parent);

  xo_render_Translate(&sprite->xform, (float)-sprite->img->w/2.0f, (float)sprite->img->h/2.0f, 0.0f);
  xo_render_Rotate(&sprite->xform, 0.0f, 0.0f, 0.0f, 1.0f);
  xo_sprite_draw(sprite);

  xo_render_EndDraw();
}

void xo_sprite_draw_bottom_left(Sprite_t* sprite) {
  xo_render_Translate(&sprite->parent, sprite->x, sprite->y, sprite->z);
  xo_render_Rotate(&sprite->parent, sprite->r, 0.0f, 0.0f, 1.0f);
  xo_render_BeginDraw(&sprite->parent);

  xo_render_Translate(&sprite->xform, 0.0f, (float)-sprite->img->h, 0.0f);
  xo_render_Rotate(&sprite->xform, 0.0f, 0.0f, 0.0f, 1.0f);
  xo_sprite_draw(sprite);

  xo_render_EndDraw();
}

void xo_sprite_draw_top_left(Sprite_t* sprite) {
  xo_render_Translate(&sprite->parent, sprite->x, sprite->y, sprite->z);
  xo_render_Rotate(&sprite->parent, sprite->r, 0.0f, 0.0f, 1.0f);
  xo_render_BeginDraw(&sprite->parent);

  xo_render_Translate(&sprite->xform, 0.0f, 0.0f, 0.0f);
  xo_render_Rotate(&sprite->xform, 0.0f, 0.0f, 0.0f, 1.0f);
  xo_sprite_draw(sprite);

  xo_render_EndDraw();
}

void xo_sprite_draw_top_right(Sprite_t* sprite) {
  xo_render_Translate(&sprite->parent, sprite->x, sprite->y, sprite->z);
  xo_render_Rotate(&sprite->parent, sprite->r, 0.0f, 0.0f, 1.0f);
  xo_render_BeginDraw(&sprite->parent);

  xo_render_Translate(&sprite->xform, (float)-sprite->img->w, 0.0f, 0.0f);
  xo_render_Rotate(&sprite->xform, 0.0f, 0.0f, 0.0f, 1.0f);
  xo_sprite_draw(sprite);

  xo_render_EndDraw();
}

void xo_sprite_draw_bottom_right(Sprite_t* sprite) {
  xo_render_Translate(&sprite->parent, sprite->x, sprite->y, sprite->z);
  xo_render_Rotate(&sprite->parent, sprite->r, 0.0f, 0.0f, 1.0f);
  xo_render_BeginDraw(&sprite->parent);

  xo_render_Translate(&sprite->xform, (float)-sprite->img->w, (float)-sprite->img->h, 0.0f);
  xo_render_Rotate(&sprite->xform, 0.0f, 0.0f, 0.0f, 1.0f);
  xo_sprite_draw(sprite);

  xo_render_EndDraw();
}