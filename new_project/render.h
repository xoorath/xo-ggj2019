#ifndef __RENDER_H_
#define __RENDER_H_

#define SCREEN_HT        240
#define SCREEN_WD        320

typedef struct {
  u16 vtxCount;
  Vtx* vtx;
  u16 idxCount;
  u16* idx;
} Mesh_t;

// see: http://level42.ca/projects/ultra64/Documentation/man/n64man/gdp/gDPSetRenderMode.html
typedef struct {
  u32 cycleType;
  u32 cycle1Mode;
  u32 cycle2Mode;
} CycleInfo_t;

// see: https://level42.ca/projects/ultra64/Documentation/man/n64man/gsp/gSPSetGeometryMode.html
typedef u32 GeometryMode_t;

// we get a different g_RenderFrameData on even and odd frames.
typedef struct {
  Mtx     projection;
  Mtx     translation;
  Mtx     rotation;
} RenderFrameData_t;

// g_RenderState persists frame to frame.
typedef struct {
  u32 placeholder;
} RenderState_t;

extern RenderState_t        g_RenderState;
extern RenderFrameData_t*   g_RenderFrameData; // changes each frame
extern Gfx*                 g_Gfx;
extern CycleInfo_t          g_DefaultCycleInfo;

extern void Render_Mesh(Mesh_t* mesh);

extern void Render_BeginFrame(void);
extern void Render_EndFrame(void);

extern void Render_BeginDraw(void);
extern void Render_EndDraw(void);

// see: https://level42.ca/projects/ultra64/Documentation/man/n64man/gsp/gSPSetGeometryMode.html
extern void Render_SetGeometryMode(GeometryMode_t geometryMode);

// see: http://level42.ca/projects/ultra64/Documentation/man/n64man/gdp/gDPSetRenderMode.html
extern void Render_SetCycleInfo(CycleInfo_t* cycleInfo);

#define GFX() (g_Gfx++)

#endif // __RENDER_H_



