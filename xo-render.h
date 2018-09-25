#ifndef __XO_RENDER_H_
#define __XO_RENDER_H_

#include <nusys.h>

//////////////////////////////////////////////////////////////////////////////////////////
// Config
//////////////////////////////////////////////////////////////////////////////////////////

#define SCREEN_HT             240
#define SCREEN_WD             320

//////////////////////////////////////////////////////////////////////////////////////////
// Data
//////////////////////////////////////////////////////////////////////////////////////////

// We only need one instance of FrameData per frame. Access it from g_FrameData after BeginFrame
typedef struct {
  Mtx projection;
} FrameData_t;

// Local transformation matricies, you need one per object you plan to render using xo_render_BeginDraw
typedef struct {
  Mtx rotation;
  Mtx translation;
} Transformation_t;

// data for this frame.
extern FrameData_t* g_FrameData;

// Pointer to the active position in the active display list.
// Assigned every time we call xo_render_BeginDisplayList_Render, for example.
// Post-increment as you use it, example: gDPFullSync(g_Glist++);
extern Gfx* g_Glist;

#define xo_render_rgba_red    0xff, 0x00, 0x00, 0xff
#define xo_render_rgba_green  0x00, 0xff, 0x00, 0xff
#define xo_render_rgba_blue   0x00, 0x00, 0xff, 0xff
#define xo_render_rgba_black  0x00, 0x00, 0x00, 0xff

//////////////////////////////////////////////////////////////////////////////////////////
// Setup and major begin/end calls
//////////////////////////////////////////////////////////////////////////////////////////

// Initialize the render code, call once at application startup
void xo_render_Init(void);

// call before any rendering code in the current frame
void xo_render_BeginFrame(void);

// call after all rendering code in the current frame
void xo_render_EndFrame(void);

// begins the rendering display list. call this before any draw calls.
void xo_render_BeginDisplayList_Render(void);

// ends the rendering display list. call after draw calls (and after xo_render_BeginDisplayList_Render)
void xo_render_EndDisplayList_Render(void);

//////////////////////////////////////////////////////////////////////////////////////////
// Per-object calls for rendering
//////////////////////////////////////////////////////////////////////////////////////////

// call after setting up your render objects transformation (t), and before actual render code.
void xo_render_BeginDraw(Transformation_t* t);

// call after render code, (and after xo_render_BeginDraw). If you have child objects to render, do that first.
void xo_render_EndDraw(void);

// apply translation of x y z to transformation t. This is not addative.
void xo_render_Translate(Transformation_t* t, f32 x, f32 y, f32 z);

// apply rotation (angle + axis x y z) to transformation t. This is not addative.
void xo_render_Rotate(Transformation_t* t, f32 angle, f32 x, f32 y, f32 z);

//////////////////////////////////////////////////////////////////////////////////////////
// Debug and misc.
//////////////////////////////////////////////////////////////////////////////////////////

// Submits draw calls for debug drawing. You don't have to do this if you're using xo_render_EndFrame.
void xo_render_DebugDraw(void);

// Renders one line of debug text, as in-order immediate mode. Lines appear in the top left of the screen in call order.
void xo_render_DebugLog(char const* msg);

// Sets the clear color to an RGB value. You only have to do this as a state change, not every frame.
void xo_render_SetClearColor(u8 r, u8 g, u8 b);


#endif // __XO_RENDER_H_