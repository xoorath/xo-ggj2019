/*
   graphic.h

   The definition of graphic and around

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

/* The screen size */
#ifndef SCREEN_HT
#define SCREEN_HT        240
#endif
#ifndef SCREEN_WD
#define SCREEN_WD        320
#endif SCREEN_WD

/* The maximum length of the display list of one task */
#ifndef GFX_GLIST_LEN
#define GFX_GLIST_LEN     2048
#endif
/* The length of the display list only for the buffer clear */
#ifndef GFX_CLEAR_GLIST_LEN
#define GFX_CLEAR_GLIST_LEN     512
#endif

/*-------------------------- define structure ------------------------------ */
/* The structure of the projection-matrix */
typedef struct {
  Mtx     projection;
  Mtx     modeling;
  Mtx     translate;
} Dynamic;

/*-------------------------------- parameter---------------------------------*/
extern Dynamic gfx_dynamic[];
extern Gfx* glistp;
extern Gfx gfx_glist[][GFX_GLIST_LEN];
extern Gfx gfx_clear_glist[][GFX_CLEAR_GLIST_LEN];
extern u32 gfx_gtask_no;
/*-------------------------------- function ---------------------------------*/
extern void gfxRCPInit(void);
extern void gfxClearCfb(void);

#endif /* _GRAPHIC_H_ */



