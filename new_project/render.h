#ifndef __RENDER_H_
#define __RENDER_H_

/* The screen size */
#define SCREEN_HT        240
#define SCREEN_WD        320

/* The maximum length of the display list of one task */
#define GFX_GLIST_LEN     2048
/* The length of the display list only for the buffer clear */
#define GFX_CLEAR_GLIST_LEN     512

/*-------------------------- define structure ------------------------------ */
/* The structure of the projection-matrix */
typedef struct {
  Mtx     projection;
  Mtx     modeling;
  Mtx     translate;
} RenderData_t;

/*-------------------------------- parameter---------------------------------*/
extern RenderData_t* g_RenderData; // changes each frame
extern Gfx* glistp;
extern Gfx gfx_glist[][GFX_GLIST_LEN];
extern Gfx gfx_clear_glist[][GFX_CLEAR_GLIST_LEN];
extern u32 gfx_gtask_no;

extern void Render_BeginFrame(void);
extern void Render_EndFrame(void);

extern void Render_BeginDraw(void);
extern void Render_EndDraw(void);
#endif // __RENDER_H_



