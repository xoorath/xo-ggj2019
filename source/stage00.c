#include <assert.h>
#include <nusys.h>
#include "main.h"
#include <xo-controller.h>
#include <xo-img.h>
#include <xo-render.h>
#include <xo-sprite.h>

#define GENERATED_IMAGE_DECLARATIONS

#include <cleft.h>
#include <cright.h>
#include <cdown.h>
#include <cup.h>

#include <enterdonsol.h>
#include <eye0.h>
#include <eye1.h>
#include <eye2.h>

#undef GENERATED_IMAGE_DECLARATIONS

static struct
{
  Sprite_t eyeSprites[3];
  Sprite_t enterSprite;

  u8 controllerPluggedIn;
  int leavingAnim;

} s_Stage00;

void initStage00(void) {
  u8 i;

  xo_render_SetClearColor(10, 10, 10);

  s_Stage00.controllerPluggedIn = FALSE;
  //donsol_audio_Init();
  //donsol_audio_PlayMainSong();

  xo_img_Load(&enterdonsol);
  xo_sprite_init(&s_Stage00.enterSprite, &enterdonsol);

  xo_img_Load(&eye0);
  xo_img_Load(&eye1);
  xo_img_Load(&eye2);
  xo_sprite_init(&s_Stage00.eyeSprites[0], &eye0);
  xo_sprite_init(&s_Stage00.eyeSprites[1], &eye1);
  xo_sprite_init(&s_Stage00.eyeSprites[2], &eye2);

  for(i = 0; i < 3; ++i) {
    s_Stage00.eyeSprites[i].x = (SCREEN_WD/2);
    s_Stage00.eyeSprites[i].y = (SCREEN_HT/2) + 20;
  }

  s_Stage00.enterSprite.x = (SCREEN_WD/2);
  s_Stage00.enterSprite.y = (SCREEN_HT/2) - 64;
  s_Stage00.leavingAnim = -1;
}

void makeDL00(void)
{
  u8 i;
  xo_render_BeginFrame();

  xo_render_BeginDisplayList_Render();

  xo_sprite_draw_center_snap(&s_Stage00.enterSprite);
  for(i = 0; i < 3; ++i) {
    xo_sprite_draw_center_snap(&s_Stage00.eyeSprites[i]);
  }


  xo_render_EndDisplayList_Render();

  if(!s_Stage00.controllerPluggedIn)
  {
    xo_render_DebugLog("no controller");
  }

  xo_render_EndFrame();
}

void updateGame00(void)
{
  u8 i;
  i = xo_controller_GetIndex(0);
  s_Stage00.controllerPluggedIn = !!xo_contoller_IsConnected(i);

  if(s_Stage00.leavingAnim > -1) {
    s_Stage00.leavingAnim++;
    if(s_Stage00.leavingAnim >= 150) {
      nuGfxFuncRemove();
      stage = 1;
    } else {
      for(i = 0; i < 3; ++i) {
        s_Stage00.eyeSprites[i].y += 1.1f + ((f32)i * -0.08f);
      }

      s_Stage00.enterSprite.y -= 1.2f;
    }
  }

  if (s_Stage00.controllerPluggedIn) {
    if (xo_controller_ButtonReleased(i, XO_BUTTON_START)) {
      s_Stage00.leavingAnim = 0;


    }
  }
}