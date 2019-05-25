#include <assert.h>
#include <nusys.h>
#include "main.h"
#include <xo-controller.h>
#include <xo-img.h>
#include <xo-render.h>
#include <xo-sprite.h>
#include "cardjoker.h"
#include "./donsol-card-images.h"

#define DECK_COUNT 54

static struct
{
  Sprite_t deck[DECK_COUNT];
  u8 controllerPluggedIn;
  u8 allocDebug;
} s_StagePlay;



void donsol_stage_play_init(void)
{
  u8 i;
  Img_t* cardImages[] = {
    &cardclubsa,
    &cardclubs2,
    &cardclubs3,
    &cardclubs4,
    &cardclubs5,
    &cardclubs6,
    &cardclubs7,
    &cardclubs8,
    &cardclubs9,
    &cardclubs10,
    &cardclubsj,
    &cardclubsq,
    &cardclubsk,

    &carddiamondsa,
    &carddiamonds2,
    &carddiamonds3,
    &carddiamonds4,
    &carddiamonds5,
    &carddiamonds6,
    &carddiamonds7,
    &carddiamonds8,
    &carddiamonds9,
    &carddiamonds10,
    &carddiamondsj,
    &carddiamondsq,
    &carddiamondsk,

    &cardspadesa,
    &cardspades2,
    &cardspades3,
    &cardspades4,
    &cardspades5,
    &cardspades6,
    &cardspades7,
    &cardspades8,
    &cardspades9,
    &cardspades10,
    &cardspadesj,
    &cardspadesq,
    &cardspadesk,

    &cardheartsa,
    &cardhearts2,
    &cardhearts3,
    &cardhearts4,
    &cardhearts5,
    &cardhearts6,
    &cardhearts7,
    &cardhearts8,
    &cardhearts9,
    &cardhearts10,
    &cardheartsj,
    &cardheartsq,
    &cardheartsk,

    &cardjoker,
    &cardjoker
  };

  s_StagePlay.controllerPluggedIn = FALSE;
  donsol_audio_Init();
  donsol_audio_PlayMainSong();

  for(i = 0; i < DECK_COUNT; ++i) {
    xo_img_Load(cardImages[i]);
    xo_sprite_init(&s_StagePlay.deck[i], cardImages[i]);
    s_StagePlay.deck[i].x = (rand() % (SCREEN_WD-50)) - (SCREEN_WD/2);
    s_StagePlay.deck[i].y = (rand() % (SCREEN_HT-50)) - (SCREEN_HT/2);
  }


}

void donsol_stage_play_render(void)
{
  u8 i;
  xo_render_BeginFrame();

  xo_render_BeginDisplayList_Render();

  for(i = 0; i < DECK_COUNT; ++i) {
    xo_sprite_draw_center_snap(&s_StagePlay.deck[i]);
  }

  xo_render_EndDisplayList_Render();
  xo_render_DebugLog("Donsol");
  if(!s_StagePlay.controllerPluggedIn)
  {
    xo_render_DebugLog("no controller");
  }

    // debug draw if player 4 has both shoulders pressed
  if(s_StagePlay.allocDebug) {
    xo_img_DebugDraw();
  }

  xo_render_EndFrame();
}

static frames_until_transfer = 100;
void donsol_stage_play_update(void)
{
  u8 i;
  f32 inputx, inputy;

  xo_controller_Update();
  // get the first plugged in controller
  i = xo_controller_GetIndex(0);

  s_StagePlay.allocDebug = 0;

  if (xo_contoller_IsConnected(i))
  {
    s_StagePlay.controllerPluggedIn = TRUE;

    xo_controller_GetAxisUnclamped(i, XO_AXIS_STICK, &inputx, &inputy);
    s_StagePlay.deck[0].x += inputx;
    s_StagePlay.deck[0].y += inputy;

    if (xo_controller_ButtonDown(i, XO_BUTTON_TRIGGER_Z)) {
      if (xo_controller_ButtonDown(i, XO_BUTTON_A)) {
        s_StagePlay.deck[0].r += 3.0f;
      } else if (xo_controller_ButtonDown(i, XO_BUTTON_B)) {
        s_StagePlay.deck[0].r -= 3.0f;
      } else {
        s_StagePlay.deck[0].r += 1.0f;
      }
    }

    s_StagePlay.allocDebug = !!xo_controller_ButtonDown(i, XO_BUTTON_BUMPER_LEFT);

    if (xo_controller_ButtonPressed(i, XO_BUTTON_START))
    //if(--frames_until_transfer <= 0)
    {
      frames_until_transfer = 10;
      nuGfxFuncRemove();
      stage = 0;
    }
  }
  else
  {
    s_StagePlay.controllerPluggedIn = FALSE;
  }
}
