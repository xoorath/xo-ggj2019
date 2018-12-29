#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "xo-img.h"
#include "xo-render.h"
#include "xo-controller.h"

static struct
{
  f32
      triPos_x,
      triPos_y,
      theta;

  Transformation_t
      parentSquare,
      childSquare,
      grandchildSquare,
      cardTop,
      cardBottom;

  u8
    controllerPluggedIn;
} s_Stage00;

void BindMesh(void);
void ApplyMesh(void);

/* The initialization of stage 0  */
void initStage00(void)
{
  s_Stage00.triPos_x = 0.0;
  s_Stage00.triPos_y = 0.0;
  s_Stage00.theta = 0.0;
  // note: transformations are set before they're used. don't bother setting them here.
  s_Stage00.controllerPluggedIn = FALSE;
  donsol_audio_Init();
  donsol_audio_PlayMainSong();
}

void makeDL00(void)
{
  xo_render_BeginFrame();

  xo_render_BeginDisplayList_Render();

  {
    xo_render_Translate(&s_Stage00.parentSquare, s_Stage00.triPos_x, s_Stage00.triPos_y, 0.0F);
    xo_render_Rotate(&s_Stage00.parentSquare, s_Stage00.theta, 0.0F, 0.0F, 1.0F);
    xo_render_BeginDraw(&s_Stage00.parentSquare);
    BindMesh();
    ApplyMesh();
    {
      xo_render_Translate(&s_Stage00.childSquare, 25.f, 0.0f, 0.0F);
      xo_render_Rotate(&s_Stage00.childSquare, s_Stage00.theta, 0.0F, 0.0F, 1.0F);
      xo_render_BeginDraw(&s_Stage00.childSquare);
      xo_img_Bind(&img_donsol_heart_ace, 0);
      BindMesh();
      xo_img_Apply(&img_donsol_heart_ace, 0);
      ApplyMesh();
      xo_img_Bind(NULL, 0);
      {
        xo_render_Translate(&s_Stage00.grandchildSquare, 2.5f, 0.0f, 0.0F);
        xo_render_Rotate(&s_Stage00.grandchildSquare, s_Stage00.theta, 0.0F, 0.0F, 1.0F);
        xo_render_BeginDraw(&s_Stage00.grandchildSquare);
        BindMesh();
        ApplyMesh();
        xo_render_EndDraw();
      }
      xo_render_EndDraw();
    }
    xo_render_EndDraw();
  }


  {
    xo_render_Translate(&s_Stage00.cardTop, 0.0f, 0.0f, 0.0F);
    xo_render_Rotate(&s_Stage00.cardTop, 0.0F, 0.0F, 0.0F, 1.0F);
    xo_render_BeginDraw(&s_Stage00.cardTop);
    xo_img_Bind(&img_donsol_heart_ace, 0);
    BindMesh();
    xo_img_Apply(&img_donsol_heart_ace, 0);
    ApplyMesh();
    xo_render_EndDraw();
  }

  xo_render_EndDisplayList_Render();
  xo_render_DebugLog("stage 00");
  if(!s_Stage00.controllerPluggedIn)
  {
    xo_render_DebugLog("no controller");
  }
  xo_render_EndFrame();
}

void updateGame00(void)
{
  u8 i;
  static f32 vel = 1.0;

  xo_controller_Update();
  // get the first plugged in controller
  i = xo_controller_GetIndex(0);

  if (xo_contoller_IsConnected(i))
  {
    s_Stage00.controllerPluggedIn = TRUE;

    xo_controller_GetAxisUnclamped(i, XO_AXIS_STICK, &s_Stage00.triPos_x, &s_Stage00.triPos_y);
    s_Stage00.triPos_x *= 80.f;
    s_Stage00.triPos_y *= 80.f;

    if (xo_controller_ButtonPressed(i, XO_BUTTON_A))
      vel = -vel;

    s_Stage00.theta = 0.f;

    //if (xo_controller_ButtonDown(i, XO_BUTTON_B))
    //  s_Stage00.theta += vel * 3.0;
    //else
    //  s_Stage00.theta += vel;

    if (xo_controller_ButtonPressed(i, XO_BUTTON_TRIGGER_Z))
      pendflag ^= 1;

    //if (xo_controller_ButtonPressed(i, XO_BUTTON_START))
    //{
    //  nuGfxFuncRemove();
    //  stage = 1;
    //}
  }
  else
  {
    s_Stage00.controllerPluggedIn = FALSE;
    s_Stage00.theta += vel;
  }
}

#define tcN 0 << 6
#define tcF 31 << 6
static Vtx shade_vtx[] = {
    {.v = {.ob = {-64, 64, -5},  .flag = 0, .tc = {tcN, tcN}, .cn = {xo_render_rgba_white}}},
    {.v = {.ob = {64, 64, -5},   .flag = 0, .tc = {tcF, tcN}, .cn = {xo_render_rgba_white}}},
    {.v = {.ob = {64, -64, -5},  .flag = 0, .tc = {tcF, tcF}, .cn = {xo_render_rgba_white}}},
    {.v = {.ob = {-64, -64, -5}, .flag = 0, .tc = {tcN, tcF}, .cn = {xo_render_rgba_white}}},
};
#undef tcN
#undef tcF


void BindMesh()
{
  gSPVertex(g_Glist++, &(shade_vtx[0]), 4, 0);

  gDPPipeSync(g_Glist++);
  gDPSetCycleType(g_Glist++, G_CYC_1CYCLE);
  gDPSetRenderMode(g_Glist++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
  gSPClearGeometryMode(g_Glist++, 0xFFFFFFFF);
  // was: G_SHADE | G_SHADING_SMOOTH
  gSPSetGeometryMode(g_Glist++,
  //G_LIGHTING |
  //G_ZBUFFER |
   G_SHADE | G_SHADING_SMOOTH
		       //| G_CULL_BACK
           );
}

void ApplyMesh()
{

  gSP2Triangles(g_Glist++, 0, 1, 2, 0, 0, 2, 3, 0);
}
