#include <assert.h>
#include <nusys.h>
#include "main.h"
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
      grandchildSquare;

  u8
    controllerPluggedIn;
} s_Stage00;

void shadetri();

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
    shadetri();
    {
      xo_render_Translate(&s_Stage00.childSquare, 25.f, 0.0f, 0.0F);
      xo_render_Rotate(&s_Stage00.childSquare, s_Stage00.theta, 0.0F, 0.0F, 1.0F);
      xo_render_BeginDraw(&s_Stage00.childSquare);
      shadetri();
      {
        xo_render_Translate(&s_Stage00.grandchildSquare, 2.5f, 0.0f, 0.0F);
        xo_render_Rotate(&s_Stage00.grandchildSquare, s_Stage00.theta, 0.0F, 0.0F, 1.0F);
        xo_render_BeginDraw(&s_Stage00.grandchildSquare);
        shadetri();
        xo_render_EndDraw();
      }
      xo_render_EndDraw();
    }
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

    if (xo_controller_ButtonDown(i, XO_BUTTON_B))
      s_Stage00.theta += vel * 3.0;
    else
      s_Stage00.theta += vel;

    if (xo_controller_ButtonPressed(i, XO_BUTTON_TRIGGER_Z))
      pendflag ^= 1;

    if (xo_controller_ButtonPressed(i, XO_BUTTON_START))
    {
      nuGfxFuncRemove();
      stage = 1;
    }
  }
  else
  {
    s_Stage00.controllerPluggedIn = FALSE;
    s_Stage00.theta += vel;
  }
}

static Vtx shade_vtx[] = {
    {.v = {.ob = {-64, 64, -5}, .flag = 0, .tc = {0, 0}, .cn = {xo_render_rgba_green}}},
    {.v = {.ob = {64, 64, -5}, .flag = 0, .tc = {0, 0}, .cn = {xo_render_rgba_black}}},
    {.v = {.ob = {64, -64, -5}, .flag = 0, .tc = {0, 0}, .cn = {xo_render_rgba_blue}}},
    {.v = {.ob = {-64, -64, -5}, .flag = 0, .tc = {0, 0}, .cn = {xo_render_rgba_red}}},
};

void shadetri()
{
  gSPVertex(g_Glist++, &(shade_vtx[0]), 4, 0);

  gDPPipeSync(g_Glist++);
  gDPSetCycleType(g_Glist++, G_CYC_1CYCLE);
  gDPSetRenderMode(g_Glist++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
  gSPClearGeometryMode(g_Glist++, 0xFFFFFFFF);
  gSPSetGeometryMode(g_Glist++, G_SHADE | G_SHADING_SMOOTH);

  gSP2Triangles(g_Glist++, 0, 1, 2, 0, 0, 2, 3, 0);
}
