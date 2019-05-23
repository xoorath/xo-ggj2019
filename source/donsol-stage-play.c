#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "xo-render.h"
#include "xo-controller.h"
#include "xo-sprite.h"

#include <cardclubs10.h>
#include <cardclubsj.h>
#include <carddiamonds8.h>
#include <cardhearts5.h>
#include <cardspades10.h>
#include <cardspadesj.h>
#include <cardclubs2.h>
#include <cardclubsk.h>
#include <carddiamonds9.h>
#include <cardhearts6.h>
#include <cardspades2.h>
#include <cardspadesk.h>
#include <cardclubs3.h>
#include <cardclubsq.h>
#include <carddiamondsa.h>
#include <cardhearts7.h>
#include <cardspades3.h>
#include <cardspadesq.h>
#include <cardclubs4.h>
#include <carddiamonds10.h>
#include <carddiamondsj.h>
#include <cardhearts8.h>
#include <cardspades4.h>
#include <cardclubs5.h>
#include <carddiamonds2.h>
#include <carddiamondsk.h>
#include <cardhearts9.h>
#include <cardspades5.h>
#include <cardclubs6.h>
#include <carddiamonds3.h>
#include <carddiamondsq.h>
#include <cardheartsa.h>
#include <cardspades6.h>
#include <cardclubs7.h>
#include <carddiamonds4.h>
#include <cardhearts10.h>
#include <cardheartsj.h>
#include <cardspades7.h>
#include <test_joker.h>
#include <cardclubs8.h>
#include <carddiamonds5.h>
#include <cardhearts2.h>
#include <cardheartsk.h>
#include <cardspades8.h>
#include <cardclubs9.h>
#include <carddiamonds6.h>
#include <cardhearts3.h>
#include <cardheartsq.h>
#include <cardspades9.h>
#include <cardclubsa.h>
#include <carddiamonds7.h>
#include <cardhearts4.h>
#include <cardjoker.h>
#include <cardspadesa.h>

static struct
{
  Sprite_t deck[2];
  u8 controllerPluggedIn;
} s_StagePlay;

void donsol_stage_play_init(void)
{
  size_t i;
  Img_t *deckImg[2];

  deckImg[0] = &test_joker;
  deckImg[1] = &test_joker;
  //=
   {
    //&cardclubs10,
    //&cardclubs2,
    // &cardclubs3,
    // &cardclubs4,
    // &cardclubs5,
    // &cardclubs6,
    // &cardclubs7,
    // &cardclubs8,
    // &cardclubs9,
    // &cardclubsa,
    // &cardclubsj,
    // &cardclubsk,
    // // &cardclubsq,
    // &carddiamonds10,
    // &carddiamonds2,
    // &carddiamonds3,
    // &carddiamonds4,
    // &carddiamonds5,
    // &carddiamonds6,
    // &carddiamonds7,
    // &carddiamonds8,
    // &carddiamonds9,
    // &carddiamondsa,
    // &carddiamondsj,
    // &carddiamondsk,
    // &carddiamondsq,
    // &cardhearts10,
    // &cardhearts2,
    // &cardhearts3,
    // &cardhearts4,
    // &cardhearts5,
    // &cardhearts6,
    // &cardhearts7,
    // &cardhearts8,
    // &cardhearts9,
    // &cardheartsa,
    // &cardheartsj,
    // &cardheartsk,
    // &cardheartsq,
    // &cardjoker,
    // &cardspades10,
    // &cardspades2,
    // &cardspades3,
    // &cardspades4,
    // &cardspades5,
    // &cardspades6,
    // &cardspades7,
    // &cardspades8,
    // &cardspades9,
    // &cardspadesa,
    // &cardspadesj,
    // &cardspadesk,
    // &cardspadesq,
    // &test_joker,
  };

  s_StagePlay.controllerPluggedIn = FALSE;
  donsol_audio_Init();
  donsol_audio_PlayMainSong();


  for(i = 0; i < sizeof(s_StagePlay.deck)/sizeof(*s_StagePlay.deck); ++i) {
    xo_img_load(deckImg[i]);
    xo_sprite_init(&s_StagePlay.deck[i], deckImg[i]);
  }
}

static int img_idx = 0;
void donsol_stage_play_render(void)
{

  xo_render_BeginFrame();

  xo_render_BeginDisplayList_Render();

  //xo_sprite_draw_center_snap(&s_StagePlay.deck[img_idx]);
  if(img_idx == sizeof(s_StagePlay.deck)/sizeof(*s_StagePlay.deck)) {
    img_idx = 0;
  } else {
    ++img_idx;
  }

  xo_render_EndDisplayList_Render();
  xo_render_DebugLog("donsol");
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
    //s_StagePlay.joker.x += inputx;
    //s_StagePlay.joker.y += inputy;

    if (xo_controller_ButtonDown(i, XO_BUTTON_TRIGGER_Z)) {
      if (xo_controller_ButtonDown(i, XO_BUTTON_A)) {
        //s_StagePlay.joker.r += 3.0f;
      } else if (xo_controller_ButtonDown(i, XO_BUTTON_B)) {
        //s_StagePlay.joker.r -= 3.0f;
      } else {
        //s_StagePlay.joker.r += 1.0f;
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
