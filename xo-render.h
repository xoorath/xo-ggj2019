#ifndef __XO_RENDER_H_
#define __XO_RENDER_H_

#include <nusys.h>

/* The screen size */
#define SCREEN_HT             240
#define SCREEN_WD             320

#define GFX_GLIST_LEN         2048
#define GFX_CLEAR_GLIST_LEN   512

typedef struct {
  Mtx     projection;
  Mtx     modeling;
  Mtx     translate;
} FrameData_t;

// todo: collapse into one.
typedef struct {
  Mtx rotation;
  Mtx translation;
} Transformation_t;

extern FrameData_t g_FrameDataCollection[];
extern FrameData_t* g_FrameData; // data for this frame.

extern void xo_render_Init(void);

extern void xo_render_BeginDisplayList_Clear(void);
extern void xo_render_EndDisplayList_Clear(void);

extern void xo_render_BeginDisplayList_Render(void);
extern void xo_render_EndDisplayList_Render(void);

extern void xo_render_BeginDraw(Transformation_t* t);
extern void xo_render_EndDraw(void);

extern void xo_render_Translate(Transformation_t* t, float x, float y, float z);
extern void xo_render_Rotate(Transformation_t* t, float angle, float x, float y, float z);

extern void xo_render_DebugDraw(void);
extern void xo_render_DebugLog(char const* msg);

extern void xo_render_Clear(void);

extern void xo_render_BeginFrame(void);
extern void xo_render_EndFrame(void);

#endif // __XO_RENDER_H_