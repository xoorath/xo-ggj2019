#include <assert.h>
#include <nusys.h>
#include "main.h"
#include <xo-controller.h>
#include <xo-img.h>
#include <xo-render.h>
#include <xo-sprite.h>
#include "cardjoker.h"
#include <cardclubs7.h>

static struct
{
  Sprite_t joker;
  u8 controllerPluggedIn;

} s_Stage00;

/* The initialization of stage 0  */
void initStage00(void)
{
  // note: transformations are set before they're used. don't bother setting them here.
  s_Stage00.controllerPluggedIn = FALSE;
  donsol_audio_Init();
  donsol_audio_PlayMainSong();

  xo_img_Load(&cardjoker);
  xo_sprite_init(&s_Stage00.joker, &cardjoker);
}

void makeDL00(void)
{
  u8 i;
  xo_render_BeginFrame();

  xo_render_BeginDisplayList_Render();

  xo_sprite_draw_center_snap(&s_Stage00.joker);

  xo_render_EndDisplayList_Render();
  xo_render_DebugLog("stage 00");
  if(!s_Stage00.controllerPluggedIn)
  {
    xo_render_DebugLog("no controller");
  }
  xo_render_EndFrame();
}

static frames_until_transfer = 10;
void updateGame00(void)
{
  u8 i;
  f32 inputx, inputy;

  xo_controller_Update();
  // get the first plugged in controller
  i = xo_controller_GetIndex(0);

  if (xo_contoller_IsConnected(i))
  {
    s_Stage00.controllerPluggedIn = TRUE;

    xo_controller_GetAxisUnclamped(i, XO_AXIS_STICK, &inputx, &inputy);
    s_Stage00.joker.x += inputx;
    s_Stage00.joker.y += inputy;

    if (xo_controller_ButtonDown(i, XO_BUTTON_TRIGGER_Z)) {
      if (xo_controller_ButtonDown(i, XO_BUTTON_A)) {
        s_Stage00.joker.r += 3.0f;
      } else if (xo_controller_ButtonDown(i, XO_BUTTON_B)) {
        s_Stage00.joker.r -= 3.0f;
      } else {
        s_Stage00.joker.r += 1.0f;
      }
    }

    if (xo_controller_ButtonPressed(i, XO_BUTTON_START))
    //if(--frames_until_transfer <= 0)
    {
      frames_until_transfer = 10;
      nuGfxFuncRemove();
      stage = 1;
    }
  }
  else
  {
    s_Stage00.controllerPluggedIn = FALSE;
  }
}