#include "donsol-card.h"

#define GENERATED_IMAGE_DECLARATIONS
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
#undef GENERATED_IMAGE_DECLARATIONS

card_t g_StartingDeck[] = {
    CARD_JO1,
    CARD_JO2,

    CARD_A | SUIT_HEARTS,
    CARD_2 | SUIT_HEARTS,
    CARD_3 | SUIT_HEARTS,
    CARD_4 | SUIT_HEARTS,
    CARD_5 | SUIT_HEARTS,
    CARD_6 | SUIT_HEARTS,
    CARD_7 | SUIT_HEARTS,
    CARD_8 | SUIT_HEARTS,
    CARD_9 | SUIT_HEARTS,
    CARD_10 | SUIT_HEARTS,
    CARD_J | SUIT_HEARTS,
    CARD_Q | SUIT_HEARTS,
    CARD_K | SUIT_HEARTS,

    CARD_A | SUIT_DIAMONDS,
    CARD_2 | SUIT_DIAMONDS,
    CARD_3 | SUIT_DIAMONDS,
    CARD_4 | SUIT_DIAMONDS,
    CARD_5 | SUIT_DIAMONDS,
    CARD_6 | SUIT_DIAMONDS,
    CARD_7 | SUIT_DIAMONDS,
    CARD_8 | SUIT_DIAMONDS,
    CARD_9 | SUIT_DIAMONDS,
    CARD_10 | SUIT_DIAMONDS,
    CARD_J | SUIT_DIAMONDS,
    CARD_Q | SUIT_DIAMONDS,
    CARD_K | SUIT_DIAMONDS,

    CARD_A | SUIT_SPADES,
    CARD_2 | SUIT_SPADES,
    CARD_3 | SUIT_SPADES,
    CARD_4 | SUIT_SPADES,
    CARD_5 | SUIT_SPADES,
    CARD_6 | SUIT_SPADES,
    CARD_7 | SUIT_SPADES,
    CARD_8 | SUIT_SPADES,
    CARD_9 | SUIT_SPADES,
    CARD_10 | SUIT_SPADES,
    CARD_J | SUIT_SPADES,
    CARD_Q | SUIT_SPADES,
    CARD_K | SUIT_SPADES,

    CARD_A | SUIT_CLUBS,
    CARD_2 | SUIT_CLUBS,
    CARD_3 | SUIT_CLUBS,
    CARD_4 | SUIT_CLUBS,
    CARD_5 | SUIT_CLUBS,
    CARD_6 | SUIT_CLUBS,
    CARD_7 | SUIT_CLUBS,
    CARD_8 | SUIT_CLUBS,
    CARD_9 | SUIT_CLUBS,
    CARD_10 | SUIT_CLUBS,
    CARD_J | SUIT_CLUBS,
    CARD_Q | SUIT_CLUBS,
    CARD_K | SUIT_CLUBS};

card_t g_ActiveDeck[] = {
    CARD_JO1,
    CARD_JO2,

    CARD_A | SUIT_HEARTS,
    CARD_2 | SUIT_HEARTS,
    CARD_3 | SUIT_HEARTS,
    CARD_4 | SUIT_HEARTS,
    CARD_5 | SUIT_HEARTS,
    CARD_6 | SUIT_HEARTS,
    CARD_7 | SUIT_HEARTS,
    CARD_8 | SUIT_HEARTS,
    CARD_9 | SUIT_HEARTS,
    CARD_10 | SUIT_HEARTS,
    CARD_J | SUIT_HEARTS,
    CARD_Q | SUIT_HEARTS,
    CARD_K | SUIT_HEARTS,

    CARD_A | SUIT_DIAMONDS,
    CARD_2 | SUIT_DIAMONDS,
    CARD_3 | SUIT_DIAMONDS,
    CARD_4 | SUIT_DIAMONDS,
    CARD_5 | SUIT_DIAMONDS,
    CARD_6 | SUIT_DIAMONDS,
    CARD_7 | SUIT_DIAMONDS,
    CARD_8 | SUIT_DIAMONDS,
    CARD_9 | SUIT_DIAMONDS,
    CARD_10 | SUIT_DIAMONDS,
    CARD_J | SUIT_DIAMONDS,
    CARD_Q | SUIT_DIAMONDS,
    CARD_K | SUIT_DIAMONDS,

    CARD_A | SUIT_SPADES,
    CARD_2 | SUIT_SPADES,
    CARD_3 | SUIT_SPADES,
    CARD_4 | SUIT_SPADES,
    CARD_5 | SUIT_SPADES,
    CARD_6 | SUIT_SPADES,
    CARD_7 | SUIT_SPADES,
    CARD_8 | SUIT_SPADES,
    CARD_9 | SUIT_SPADES,
    CARD_10 | SUIT_SPADES,
    CARD_J | SUIT_SPADES,
    CARD_Q | SUIT_SPADES,
    CARD_K | SUIT_SPADES,

    CARD_A | SUIT_CLUBS,
    CARD_2 | SUIT_CLUBS,
    CARD_3 | SUIT_CLUBS,
    CARD_4 | SUIT_CLUBS,
    CARD_5 | SUIT_CLUBS,
    CARD_6 | SUIT_CLUBS,
    CARD_7 | SUIT_CLUBS,
    CARD_8 | SUIT_CLUBS,
    CARD_9 | SUIT_CLUBS,
    CARD_10 | SUIT_CLUBS,
    CARD_J | SUIT_CLUBS,
    CARD_Q | SUIT_CLUBS,
    CARD_K | SUIT_CLUBS};

void donsol_card_ClearFlippedBit()
{
  u8 i;
  for(i = 0; i < DECK_SIZE; ++i)
  {
    g_ActiveDeck[i] &= ~CARDSTATE_FLIPPED;
  }
}

void donsol_card_ShuffleDeck()
{
  u8 i, r;
  card_t t;
  for(i = 0; i < DECK_SIZE; ++i)
  {
    r = rand() % DECK_SIZE;
    t = g_ActiveDeck[i];
    g_ActiveDeck[i] = g_ActiveDeck[r];
    g_ActiveDeck[r] = t;
  }

}