#include "donsol-card.h"

#define GENERATED_IMAGE_DECLARATIONS
#include "./donsol-card-images.h"
// todo: move
#include <cleft.h>
#include <cright.h>
#include <cdown.h>
#include <cup.h>
#undef GENERATED_IMAGE_DECLARATIONS

#ifdef _GU_H_
#   define donsolRandom guRandom
#else
#   include <stdlib.h>
#   define donsolRandom rand
#endif

u8 donsol_card_IsJoker(Card_t card) {
  return (card & CARD_MASK) >= CARD_JO1;
}

u8 donsol_card_IsFace(Card_t card)
{
  card = card & CARD_MASK;
  return card >= CARD_J && CARD_J <= CARD_K;
}

u8 donsol_card_IsNumeric(Card_t card)
{
  card &= CARD_MASK;
  return card > CARD_A && card <= CARD_10;
}

u8 donsol_card_GetNumericValue(Card_t card)
{
  return card & CARD_MASK;
}

u8 donsol_card_GetSuit(Card_t card)
{
  return (card & SUIT_MASK);
}

u8 donsol_card_IsHearts(Card_t card)
{
  return donsol_card_GetSuit(card) == SUIT_HEARTS;
}

u8 donsol_card_IsDiamonds(Card_t card)
{
  return donsol_card_GetSuit(card) == SUIT_DIAMONDS;
}

u8 donsol_card_IsSpades(Card_t card)
{
  return donsol_card_GetSuit(card) == SUIT_SPADES;
}

u8 donsol_card_IsClubs(Card_t card)
{
  return donsol_card_GetSuit(card) == SUIT_CLUBS;
}

u8 donsol_card_IsFlipped(Card_t card)
{
  return !!(card & CARDSTATE_FLIPPED);
}

void donsol_card_ClearFlippedBit(Card_t* collection, u8 count) {
  u8 i;
  for(i = 0; i < count; ++i) {
    collection[i] &= ~CARDSTATE_FLIPPED;
  }
}

void donsol_card_ShuffleDeck(Card_t* collection, u8 count) {
  u8 i, r;
  Card_t t;
  for(i = 0; i < count; ++i) {
    r = donsolRandom() % count;
    t = collection[i];
    collection[i] = collection[r];
    collection[r] = t;
  }
}