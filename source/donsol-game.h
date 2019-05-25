#ifndef __DONSOL_GAME_H_
#define __DONSOL_GAME_H_

#include <xo-types.h>

#include "donsol-card.h"

typedef enum {
    DONSOL_STATUS_WELCOME,

    // The card trying to be used has already been used
    DONSOL_STATUS_ALREADY_USED,

    DONSOL_STATUS_POTION_WASTED,
    DONSOL_STATUS_POTION_USED,

    DONSOL_SHIELD_EQUIPED,
    DONSOL_SHIELD_BROKE,
    DONSOL_WON_FIGHT,
    DONSOL_LOST_FIGHT,

    DONSOL_STATUS_CANT_RUN,

    DONSOL_STATUS_YOU_WIN
} DonsolStatusUpdate_e;

typedef struct {
    Card_t* dcard;
    char simpleName[32];
    char name[32];
    u8 power;
    bool isMonster, isPotion, isShield;
} DonsolCardDescription_t;

typedef struct {
    // last change to hp/xp/dp for use in UI
    s8 hpDelta, xpDelta, dpDelta;

    // current hp/xp/dp
    s8 hp, xp, dp;
    s8 shieldBreakLimit;

    // restrictions
    bool canDrink;
    bool canRun;

    // lets you run infinitely before taking you first action
    bool hasTakenAction;

    // only restarting actions will be allowed
    bool wonOrDied;

    // The 4 active slots.
    DonsolCardDescription_t slots[4];

    void(*onError)(char const*);
    void(*onStatusUpdate)(DonsolStatusUpdate_e, char const*);
} DonsolGame_t;

// init the game object
void donsol_game_start(DonsolGame_t* game);

void donsol_game_pick_run(DonsolGame_t* game);
void donsol_game_pick_card(DonsolGame_t* game, u8 index); // index can be: [1,2,3,4]

#endif // __DONSOL_GAME_H_