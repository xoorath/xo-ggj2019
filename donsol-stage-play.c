#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "xo-render.h"
#include "xo-controller.h"
#include "xo-sprite.h"
#include "test_joker.h"

static struct
{
  Sprite_t joker;
  u8 controllerPluggedIn;
} s_StagePlay;

void donsol_stage_play_init(void)
{
  s_StagePlay.controllerPluggedIn = FALSE;
  donsol_audio_Init();
  donsol_audio_PlayMainSong();

  xo_img_Load(&test_joker);
  xo_sprite_init(&s_StagePlay.joker, &test_joker);
}

void donsol_stage_play_render(void)
{
  xo_render_BeginFrame();

  xo_render_BeginDisplayList_Render();

  xo_sprite_draw_center_snap(&s_StagePlay.joker);

  xo_render_EndDisplayList_Render();
  xo_render_DebugLog("stage 01");
  xo_render_DebugLog("This stage has more text.");
  if(!s_StagePlay.controllerPluggedIn)
  {
    xo_render_DebugLog("no controller");
  }
  xo_render_EndFrame();
}

void donsol_stage_play_update(void)
{
  u8 i;
  f32 inputx, inputy;

  xo_controller_Update();
  // get the first plugged in controller
  i = xo_controller_GetIndex(0);

  if (xo_contoller_IsConnected(i))
  {
    s_StagePlay.controllerPluggedIn = TRUE;

    xo_controller_GetAxisUnclamped(i, XO_AXIS_STICK, &inputx, &inputy);
    s_StagePlay.joker.x += inputx;
    s_StagePlay.joker.y += inputy;

    if (xo_controller_ButtonDown(i, XO_BUTTON_TRIGGER_Z)) {
      if (xo_controller_ButtonDown(i, XO_BUTTON_A)) {
        s_StagePlay.joker.r += 3.0f;
      } else if (xo_controller_ButtonDown(i, XO_BUTTON_B)) {
        s_StagePlay.joker.r -= 3.0f;
      } else {
        s_StagePlay.joker.r += 1.0f;
      }
    }

    if (xo_controller_ButtonPressed(i, XO_BUTTON_START))
    {
      nuGfxFuncRemove();
      stage = 0;
    }
  }
  else
  {
    s_StagePlay.controllerPluggedIn = FALSE;
  }
}
