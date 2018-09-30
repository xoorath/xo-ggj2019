#ifndef __DONSOL_CARD_H_
#define __DONSOL_CARD_H_

#include <PR/ultratypes.h>

typedef u8 card_t;

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

#define DECK_SIZE 54
extern card_t g_StartingDeck[];
extern card_t g_ActiveDeck[];

inline u8 donsol_card_IsJoker(card_t card)
{
  return (card & CARD_MASK) >= CARD_JO1;
}

inline u8 donsol_card_IsFace(card_t card)
{
  card = card & CARD_MASK;
  return card >= CARD_J && CARD_J <= CARD_K;
}

inline u8 donsol_card_IsNumeric(card_t card)
{
  return (card & CARD_MASK) <= CARD_10;
}

inline u8 donsol_card_IsHearts(card_t card)
{
  return (card & SUIT_MASK) == SUIT_HEARTS;
}

inline u8 donsol_card_IsDiamonds(card_t card)
{
  return (card & SUIT_MASK) == SUIT_DIAMONDS;
}

inline u8 donsol_card_IsSpades(card_t card)
{
  return (card & SUIT_MASK) == SUIT_SPADES;
}

inline u8 donsol_card_IsClubs(card_t card)
{
  return (card & SUIT_MASK) == SUIT_CLUBS;
}

inline u8 donsol_card_IsFlipped(card_t card)
{
  return (card & SUIT_MASK) == SUIT_CLUBS;
}

void donsol_card_ClearFlippedBit();
void donsol_card_ShuffleDeck();

#endif // __DONSOL_CARD_H_