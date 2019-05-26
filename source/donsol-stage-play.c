#include <assert.h>
#include <nusys.h>
#include "main.h"
#include <xo-controller.h>
#include <xo-img.h>
#include <xo-math.h>
#include <xo-render.h>
#include <xo-sprite.h>
#include <cleft.h>
#include <cright.h>
#include <cdown.h>
#include <cup.h>
#include "./donsol-card-images.h"
#include "./donsol-game.h"

// todo: check if needed
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static struct
{
  DonsolGame_t game;

  // game data
  bool potionJustWasted;

  // ui
  Sprite_t cbuttons[4];
  Sprite_t cards[4];
  Sprite_t labels[4];
  u8 hpPosX, hpPosY;
  u8 dpPosX, dpPosY;
  u8 xpPosX, xpPosY;
  char statusText[64];
  char errorText[1024];

  // input
  bool controllerPluggedIn;
  bool allocDebug;

  // data
  Img_t* cardImages[54];
  Img_t* cardLabels[54];
} s_StagePlay;

void donsol_gamecb_on_error(char const* msg) {
    memcpy(s_StagePlay.errorText, msg, strlen(msg)+1);
}

void donsol_gamecb_on_update(DonsolStatusUpdate_e update, char const* msg) {
    sprintf(s_StagePlay.statusText, "%s", msg);
    s_StagePlay.potionJustWasted = (update == DONSOL_STATUS_POTION_WASTED);
}

// gets a linear index that can be used in an array (such as cardImages)
u8 donsol_stage_play_card_to_idx(Card_t card) {
  // check jokers first, since in data they're considered hearts
  if(donsol_card_IsJoker(card)) {
    if(card & CARD_JO1) {
      return 52;
    }
    return 53;
  }
  else if(donsol_card_IsHearts(card)) {
    return donsol_card_GetNumericValue(card);
  }
  else if(donsol_card_IsDiamonds(card)) {
    return donsol_card_GetNumericValue(card) + 13;
  }
  else if(donsol_card_IsSpades(card)) {
    return donsol_card_GetNumericValue(card) + 26;
  }
  else if(donsol_card_IsClubs(card)) {
    return donsol_card_GetNumericValue(card) + 39;
  }
  return 54; // error case
}

Img_t* donsol_stage_play_card_to_cardimg(Card_t card) {
  u8 idx = donsol_stage_play_card_to_idx(card);
  if(idx>53) {
    return &test_joker;
  }
  return s_StagePlay.cardImages[idx];
}

Img_t* donsol_stage_play_card_to_labelimg(Card_t card) {
  u8 idx = donsol_stage_play_card_to_idx(card);
  if(idx>53) {
    return &test_joker;
  }
  return s_StagePlay.cardLabels[idx];
}

void donsol_stage_play_init(void)
{
  u8 xSpacing;
  u8 i = 0;

  memset(&s_StagePlay.game, 0, sizeof(s_StagePlay.game));
  memset(s_StagePlay.errorText, 0, sizeof(s_StagePlay.errorText));
  memset(s_StagePlay.statusText, 0, sizeof(s_StagePlay.statusText));

  s_StagePlay.game.onError = donsol_gamecb_on_error;
  s_StagePlay.game.onStatusUpdate = donsol_gamecb_on_update;

  s_StagePlay.cardImages[i++] = &cardheartsa;
  s_StagePlay.cardImages[i++] = &cardhearts2;
  s_StagePlay.cardImages[i++] = &cardhearts3;
  s_StagePlay.cardImages[i++] = &cardhearts4;
  s_StagePlay.cardImages[i++] = &cardhearts5;
  s_StagePlay.cardImages[i++] = &cardhearts6;
  s_StagePlay.cardImages[i++] = &cardhearts7;
  s_StagePlay.cardImages[i++] = &cardhearts8;
  s_StagePlay.cardImages[i++] = &cardhearts9;
  s_StagePlay.cardImages[i++] = &cardhearts10;
  s_StagePlay.cardImages[i++] = &cardheartsj;
  s_StagePlay.cardImages[i++] = &cardheartsq;
  s_StagePlay.cardImages[i++] = &cardheartsk;
  s_StagePlay.cardImages[i++] = &carddiamondsa;
  s_StagePlay.cardImages[i++] = &carddiamonds2;
  s_StagePlay.cardImages[i++] = &carddiamonds3;
  s_StagePlay.cardImages[i++] = &carddiamonds4;
  s_StagePlay.cardImages[i++] = &carddiamonds5;
  s_StagePlay.cardImages[i++] = &carddiamonds6;
  s_StagePlay.cardImages[i++] = &carddiamonds7;
  s_StagePlay.cardImages[i++] = &carddiamonds8;
  s_StagePlay.cardImages[i++] = &carddiamonds9;
  s_StagePlay.cardImages[i++] = &carddiamonds10;
  s_StagePlay.cardImages[i++] = &carddiamondsj;
  s_StagePlay.cardImages[i++] = &carddiamondsq;
  s_StagePlay.cardImages[i++] = &carddiamondsk;
  s_StagePlay.cardImages[i++] = &cardspadesa;
  s_StagePlay.cardImages[i++] = &cardspades2;
  s_StagePlay.cardImages[i++] = &cardspades3;
  s_StagePlay.cardImages[i++] = &cardspades4;
  s_StagePlay.cardImages[i++] = &cardspades5;
  s_StagePlay.cardImages[i++] = &cardspades6;
  s_StagePlay.cardImages[i++] = &cardspades7;
  s_StagePlay.cardImages[i++] = &cardspades8;
  s_StagePlay.cardImages[i++] = &cardspades9;
  s_StagePlay.cardImages[i++] = &cardspades10;
  s_StagePlay.cardImages[i++] = &cardspadesj;
  s_StagePlay.cardImages[i++] = &cardspadesq;
  s_StagePlay.cardImages[i++] = &cardspadesk;
  s_StagePlay.cardImages[i++] = &cardclubsa;
  s_StagePlay.cardImages[i++] = &cardclubs2;
  s_StagePlay.cardImages[i++] = &cardclubs3;
  s_StagePlay.cardImages[i++] = &cardclubs4;
  s_StagePlay.cardImages[i++] = &cardclubs5;
  s_StagePlay.cardImages[i++] = &cardclubs6;
  s_StagePlay.cardImages[i++] = &cardclubs7;
  s_StagePlay.cardImages[i++] = &cardclubs8;
  s_StagePlay.cardImages[i++] = &cardclubs9;
  s_StagePlay.cardImages[i++] = &cardclubs10;
  s_StagePlay.cardImages[i++] = &cardclubsj;
  s_StagePlay.cardImages[i++] = &cardclubsq;
  s_StagePlay.cardImages[i++] = &cardclubsk;
  s_StagePlay.cardImages[i++] = &cardjoker;
  s_StagePlay.cardImages[i++] = &cardjoker;

  i = 0;

  s_StagePlay.cardLabels[i++] = &cardheartsa_l;
  s_StagePlay.cardLabels[i++] = &cardhearts2_l;
  s_StagePlay.cardLabels[i++] = &cardhearts3_l;
  s_StagePlay.cardLabels[i++] = &cardhearts4_l;
  s_StagePlay.cardLabels[i++] = &cardhearts5_l;
  s_StagePlay.cardLabels[i++] = &cardhearts6_l;
  s_StagePlay.cardLabels[i++] = &cardhearts7_l;
  s_StagePlay.cardLabels[i++] = &cardhearts8_l;
  s_StagePlay.cardLabels[i++] = &cardhearts9_l;
  s_StagePlay.cardLabels[i++] = &cardhearts10_l;
  s_StagePlay.cardLabels[i++] = &cardheartsj_l;
  s_StagePlay.cardLabels[i++] = &cardheartsq_l;
  s_StagePlay.cardLabels[i++] = &cardheartsk_l;
  s_StagePlay.cardLabels[i++] = &carddiamondsa_l;
  s_StagePlay.cardLabels[i++] = &carddiamonds2_l;
  s_StagePlay.cardLabels[i++] = &carddiamonds3_l;
  s_StagePlay.cardLabels[i++] = &carddiamonds4_l;
  s_StagePlay.cardLabels[i++] = &carddiamonds5_l;
  s_StagePlay.cardLabels[i++] = &carddiamonds6_l;
  s_StagePlay.cardLabels[i++] = &carddiamonds7_l;
  s_StagePlay.cardLabels[i++] = &carddiamonds8_l;
  s_StagePlay.cardLabels[i++] = &carddiamonds9_l;
  s_StagePlay.cardLabels[i++] = &carddiamonds10_l;
  s_StagePlay.cardLabels[i++] = &carddiamondsj_l;
  s_StagePlay.cardLabels[i++] = &carddiamondsq_l;
  s_StagePlay.cardLabels[i++] = &carddiamondsk_l;
  s_StagePlay.cardLabels[i++] = &cardspadesa_l;
  s_StagePlay.cardLabels[i++] = &cardspades2_l;
  s_StagePlay.cardLabels[i++] = &cardspades3_l;
  s_StagePlay.cardLabels[i++] = &cardspades4_l;
  s_StagePlay.cardLabels[i++] = &cardspades5_l;
  s_StagePlay.cardLabels[i++] = &cardspades6_l;
  s_StagePlay.cardLabels[i++] = &cardspades7_l;
  s_StagePlay.cardLabels[i++] = &cardspades8_l;
  s_StagePlay.cardLabels[i++] = &cardspades9_l;
  s_StagePlay.cardLabels[i++] = &cardspades10_l;
  s_StagePlay.cardLabels[i++] = &cardspadesj_l;
  s_StagePlay.cardLabels[i++] = &cardspadesq_l;
  s_StagePlay.cardLabels[i++] = &cardspadesk_l;
  s_StagePlay.cardLabels[i++] = &cardclubsa_l;
  s_StagePlay.cardLabels[i++] = &cardclubs2_l;
  s_StagePlay.cardLabels[i++] = &cardclubs3_l;
  s_StagePlay.cardLabels[i++] = &cardclubs4_l;
  s_StagePlay.cardLabels[i++] = &cardclubs5_l;
  s_StagePlay.cardLabels[i++] = &cardclubs6_l;
  s_StagePlay.cardLabels[i++] = &cardclubs7_l;
  s_StagePlay.cardLabels[i++] = &cardclubs8_l;
  s_StagePlay.cardLabels[i++] = &cardclubs9_l;
  s_StagePlay.cardLabels[i++] = &cardclubs10_l;
  s_StagePlay.cardLabels[i++] = &cardclubsj_l;
  s_StagePlay.cardLabels[i++] = &cardclubsq_l;
  s_StagePlay.cardLabels[i++] = &cardclubsk_l;
  s_StagePlay.cardLabels[i++] = &cardjoker_l;
  s_StagePlay.cardLabels[i++] = &cardjoker_l;


  for(i = 0; i < 54; ++i) {
    xo_img_Load(s_StagePlay.cardImages[i]);
    xo_img_Load(s_StagePlay.cardLabels[i]);
  }

  xo_img_Load(&cardback);
  xo_img_Load(&test_joker);
  xo_img_Load(&cleft);
  xo_img_Load(&cright);
  xo_img_Load(&cup);
  xo_img_Load(&cdown);

  xo_sprite_init(&s_StagePlay.cbuttons[0], &cleft);
  xo_sprite_init(&s_StagePlay.cbuttons[1], &cup);
  xo_sprite_init(&s_StagePlay.cbuttons[2], &cright);
  xo_sprite_init(&s_StagePlay.cbuttons[3], &cdown);

  for(i = 0; i < 4; ++i) {
    xo_sprite_init(&s_StagePlay.cards[i], &cardback);
    xo_sprite_init(&s_StagePlay.labels[i], &cardback);
  }

  s_StagePlay.hpPosX = 2;
  s_StagePlay.hpPosY = 26;

  s_StagePlay.dpPosX = s_StagePlay.hpPosX + 13;
  s_StagePlay.dpPosY = 26;

  s_StagePlay.xpPosX = s_StagePlay.dpPosX + 15;
  s_StagePlay.xpPosY = 26;

  xSpacing = 0;
  for(i = 0; i < 4; ++i) {
    s_StagePlay.cards[i].x = (f32)(s32)((32.f) + 17.f + (64.f*i) + xSpacing);
    s_StagePlay.cards[i].y = (f32)(s32)(87.f * 2);
    xSpacing += 10;

    s_StagePlay.labels[i].x = (f32)(s32)(s_StagePlay.cards[i].x);
    s_StagePlay.labels[i].y = (f32)(s32)(s_StagePlay.cards[i].y - (87.f/2.f) - 36.f);

    s_StagePlay.cbuttons[i].x = (f32)(s32)(s_StagePlay.labels[i].x - 26);
    s_StagePlay.cbuttons[i].y = (f32)(s32)(s_StagePlay.labels[i].y + 24);

  }

  donsol_game_start(&s_StagePlay.game);

  s_StagePlay.controllerPluggedIn = false;
  //donsol_audio_Init();
  //donsol_audio_PlayMainSong();
}

void donsol_stage_play_render(void)
{
  u8 i;
  char textBuffer[32] = {0};

  xo_render_BeginFrame();
  xo_render_BeginDisplayList_Render();

  //////////////////////////////////////////////////////////////////////////////// Status Text
  if(s_StagePlay.statusText[0] != '\0') {
    nuDebConTextColor(0, NU_DEB_CON_TEXT_WHITE);
    nuDebConTextPos(0, 2, 22);
    nuDebConCPuts(NU_DEB_CON_WINDOW0, s_StagePlay.statusText);
  }

  //////////////////////////////////////////////////////////////////////////////// HP
  if(s_StagePlay.potionJustWasted) {
    sprintf(textBuffer, "%02d +0", s_StagePlay.game.hp);
  } else if(s_StagePlay.game.hpDelta != 0) {
    sprintf(textBuffer, "%02d %c%d", s_StagePlay.game.hp, s_StagePlay.game.hpDelta>0?'+':'-', abs(s_StagePlay.game.hpDelta));
  } else {
    sprintf(textBuffer, "%02d", s_StagePlay.game.hp);
  }

  nuDebConTextColor(0, NU_DEB_CON_TEXT_RED);
  nuDebConTextPos(0, s_StagePlay.hpPosX, s_StagePlay.hpPosY);
  nuDebConCPuts(NU_DEB_CON_WINDOW0, "HP");
  nuDebConTextColor(0, NU_DEB_CON_TEXT_LIGHTRED);
  nuDebConTextPos(0, s_StagePlay.hpPosX+3, s_StagePlay.hpPosY);
  nuDebConCPuts(NU_DEB_CON_WINDOW0, textBuffer);


  //////////////////////////////////////////////////////////////////////////////// DP
  if(s_StagePlay.game.shieldBreakLimit < 0) {
    if(s_StagePlay.game.dp == 0) {
      sprintf(textBuffer, "none");
    }
    else {
      sprintf(textBuffer, "%02d new", s_StagePlay.game.dp);
    }
  } else if(s_StagePlay.game.shieldBreakLimit > 0) {
    sprintf(textBuffer, "%02d/%02d", s_StagePlay.game.dp, s_StagePlay.game.shieldBreakLimit);
  } else {
    sprintf(textBuffer, "none", s_StagePlay.game.dp);
  }
  nuDebConTextColor(0, NU_DEB_CON_TEXT_BLUE);
  nuDebConTextPos(0, s_StagePlay.dpPosX, s_StagePlay.dpPosY);
  nuDebConCPuts(NU_DEB_CON_WINDOW0, "DP");
  nuDebConTextColor(0, NU_DEB_CON_TEXT_LIGHTBLUE);
  nuDebConTextPos(0, s_StagePlay.dpPosX+3, s_StagePlay.dpPosY);
  nuDebConCPuts(NU_DEB_CON_WINDOW0, textBuffer);

  //////////////////////////////////////////////////////////////////////////////// XP
  if(s_StagePlay.game.xpDelta > 0) {
    sprintf(textBuffer, "%02d %c%d", s_StagePlay.game.xp, s_StagePlay.game.xpDelta>0?'+':'-', abs(s_StagePlay.game.xpDelta));
  } else {
    sprintf(textBuffer, "%02d", s_StagePlay.game.xp);
  }

  nuDebConTextColor(0, NU_DEB_CON_TEXT_LIGHTBLACK);
  nuDebConTextPos(0, s_StagePlay.xpPosX, s_StagePlay.xpPosY);
  nuDebConCPuts(NU_DEB_CON_WINDOW0, "XP");
  nuDebConTextColor(0, NU_DEB_CON_TEXT_WHITE);
  nuDebConTextPos(0, s_StagePlay.xpPosX+3, s_StagePlay.xpPosY);
  nuDebConCPuts(NU_DEB_CON_WINDOW0, textBuffer);


  //////////////////////////////////////////////////////////////////////////////// CARDS
  for(i = 0; i < 4; ++i) {
    Card_t c = *s_StagePlay.game.slots[i].dcard;
    if(donsol_card_IsFlipped(c)) {
      s_StagePlay.cards[i].img = &cardback;
      xo_sprite_draw_center_snap(&s_StagePlay.cards[i]);
    } else {
      s_StagePlay.cards[i].img = donsol_stage_play_card_to_cardimg(c);
      s_StagePlay.labels[i].img = donsol_stage_play_card_to_labelimg(c);

      xo_sprite_draw_center_snap(&s_StagePlay.cards[i]);
      xo_sprite_draw_center_snap(&s_StagePlay.labels[i]);
      xo_sprite_draw_center_snap(&s_StagePlay.cbuttons[i]);
    }
  }

  xo_render_EndDisplayList_Render();

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

void donsol_stage_play_update(void)
{
  u8 i;

  // get the first plugged in controller
  i = xo_controller_GetIndex(0);

  s_StagePlay.allocDebug = 0;

  if (s_StagePlay.controllerPluggedIn = xo_contoller_IsConnected(i))
  {
    // QUIT
    if(xo_controller_ButtonReleased(i, XO_BUTTON_B)) {
      nuGfxFuncRemove();
      stage = 0;
    }
    // START GAME
    else if(xo_controller_ButtonReleased(i, XO_BUTTON_A) || xo_controller_ButtonReleased(i, XO_BUTTON_START)) {
      donsol_game_start(&s_StagePlay.game);
    }
    // RUN
    else if(xo_controller_ButtonReleased(i, XO_BUTTON_BUMPER_RIGHT)) {
      donsol_game_pick_run(&s_StagePlay.game);
    }
    // PICK CARDS
    else if(xo_controller_ButtonReleased(i, XO_BUTTON_C_LEFT)) {
      donsol_game_pick_card(&s_StagePlay.game, 1);
    } else if(xo_controller_ButtonReleased(i, XO_BUTTON_C_UP)) {
      donsol_game_pick_card(&s_StagePlay.game, 2);
    } else if(xo_controller_ButtonReleased(i, XO_BUTTON_C_RIGHT)) {
      donsol_game_pick_card(&s_StagePlay.game, 3);
    } else if(xo_controller_ButtonReleased(i, XO_BUTTON_C_DOWN)) {
      donsol_game_pick_card(&s_StagePlay.game, 4);
    }

    s_StagePlay.allocDebug = !!xo_controller_ButtonDown(i, XO_BUTTON_BUMPER_LEFT);

  }
}
