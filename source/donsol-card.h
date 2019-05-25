#ifndef __DONSOL_CARD_H_
#define __DONSOL_CARD_H_

#include <xo-types.h>

typedef u8 Card_t;

enum {
  // bits 1, 2, 3, 4
  CARD_A    = 0  << 0,
  CARD_2    = 1  << 0,
  CARD_3    = 2  << 0,
  CARD_4    = 3  << 0,
  CARD_5    = 4  << 0,
  CARD_6    = 5  << 0,
  CARD_7    = 6  << 0,
  CARD_8    = 7  << 0,
  CARD_9    = 8  << 0,
  CARD_10   = 9  << 0,
  CARD_J    = 10 << 0,
  CARD_Q    = 11 << 0,
  CARD_K    = 12 << 0,
  CARD_JO1  = 13 << 0,
  CARD_JO2  = 14 << 0,
  CARD_MASK = 0x0f,

  // bits 5, 6
  SUIT_HEARTS   = 0 << 4,
  SUIT_DIAMONDS = 1 << 4,
  SUIT_SPADES   = 2 << 4,
  SUIT_CLUBS    = 3 << 4,
  SUIT_MASK = SUIT_HEARTS | SUIT_DIAMONDS | SUIT_SPADES | SUIT_CLUBS,

  // bits 7
  CARDSTATE_FLIPPED = 1 << 7,
  CARDSTATE_MASK = CARDSTATE_FLIPPED
};

u8 donsol_card_IsJoker(Card_t card);
u8 donsol_card_IsFace(Card_t card);
u8 donsol_card_IsNumeric(Card_t card);
u8 donsol_card_GetNumericValue(Card_t card);
u8 donsol_card_GetSuit(Card_t card);
u8 donsol_card_IsHearts(Card_t card);
u8 donsol_card_IsDiamonds(Card_t card);
u8 donsol_card_IsSpades(Card_t card);
u8 donsol_card_IsClubs(Card_t card);
u8 donsol_card_IsFlipped(Card_t card);

void donsol_card_ClearFlippedBit(Card_t* collection, u8 count);
void donsol_card_ShuffleDeck(Card_t* collection, u8 count);

#endif // __DONSOL_CARD_H_