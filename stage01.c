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
      childSquare;

  u8
    controllerPluggedIn;
} s_Stage01;

void shadetri();

/* The initialization of stage 1 */
void initStage01(void)
{
  s_Stage01.triPos_x = 0.0;
  s_Stage01.triPos_y = 0.0;
  s_Stage01.theta = 0.0;

  s_Stage01.controllerPluggedIn = FALSE;
  donsol_audio_Init();
  donsol_audio_PlayMainSong();
}

/* Make the display list for stage 1 and activate the task */
void makeDL01(void)
{
  xo_render_BeginFrame();

  xo_render_BeginDisplayList_Render();

  {
    xo_render_Translate(&s_Stage01.parentSquare, s_Stage01.triPos_x, s_Stage01.triPos_y, 0.0F);
    xo_render_Rotate(&s_Stage01.parentSquare, s_Stage01.theta, 0.0F, 0.0F, 1.0F);
    xo_render_BeginDraw(&s_Stage01.parentSquare);
    shadetri();
    {
      xo_render_Translate(&s_Stage01.childSquare, 25.f, 0.0f, 0.0F);
      xo_render_Rotate(&s_Stage01.childSquare, s_Stage01.theta, 0.0F, 0.0F, 1.0F);
      xo_render_BeginDraw(&s_Stage01.childSquare);
      shadetri();
      xo_render_EndDraw();
    }
    xo_render_EndDraw();
  }

  xo_render_EndDisplayList_Render();
  xo_render_DebugLog("stage 01");
  xo_render_DebugLog("This stage has more text.");
  if(!s_Stage01.controllerPluggedIn)
  {
    xo_render_DebugLog("no controller");
  }
  xo_render_EndFrame();
}

/* The game progressing process for stage 1 */
void updateGame01(void)
{
  u8 i;
  static f32 vel = 1.0;

  xo_controller_Update();
  // get the first plugged in controller
  i = xo_controller_GetIndex(0);

  if (xo_contoller_IsConnected(i))
  {
    s_Stage01.controllerPluggedIn = TRUE;

    xo_controller_GetAxisUnclamped(i, XO_AXIS_STICK, &s_Stage01.triPos_x, &s_Stage01.triPos_y);
    s_Stage01.triPos_x *= 80.f;
    s_Stage01.triPos_y *= 80.f;

    if (xo_controller_ButtonPressed(i, XO_BUTTON_A))
      vel = -vel;

    if (xo_controller_ButtonDown(i, XO_BUTTON_B))
      s_Stage01.theta += vel * 3.0;
    else
      s_Stage01.theta += vel;

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
    s_Stage01.controllerPluggedIn = FALSE;
    s_Stage01.theta += vel;
  }
}
