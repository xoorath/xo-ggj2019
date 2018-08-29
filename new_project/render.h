#ifndef _RENDER_H_
#define _RENDER_H_
#include <nusys.h>

#define SCREEN_HT         240
#define SCREEN_WD         320
#define GFX_GLIST_LEN     2048

typedef struct {
  Mtx     projection;
  Mtx     modeling;
  Mtx     translate;
} RenderState_t;

typedef struct {
  u16   vtxCount;
  Vtx*  vtx;
  u16   idxCount;
  u16*  idx;
} Mesh_t;

typedef struct {
  unsigned int cycleType;
  unsigned int renderMode0, renderMode1;
  unsigned int geometryMode;
} MeshSettings_t;

extern void Render_MeshDefault(Mesh_t* mesh);
extern void Render_Mesh(Mesh_t* mesh, MeshSettings_t* settings);

extern void Render_BeginFrame(void);
extern void Render_EndFrame(void);

extern void Render_BeginDraw(void);
extern void Render_EndDraw(void);

#define GFX() (g_Gfx++)

#ifdef DNU_DEBUG
# define GFX_CHECK() assert((g_Gfx - gfx_glist[g_RenderFrameIdx]) < GFX_GLIST_LEN);
#else
# define GFX_CHECK()
#endif

extern RenderState_t* g_RenderState; // changes every frame.
extern Gfx* g_Gfx;
extern Gfx gfx_glist[][GFX_GLIST_LEN];
extern u32 g_RenderFrameIdx;

#endif // _RENDER_H_