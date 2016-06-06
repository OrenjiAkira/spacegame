
#include "debug.h"
#include "game.h"
#include "entity.h"
#include "action.h"
#include "actions/movefwd.h"
#include "actions/turndir.h"
#include "actions/autodie.h"
#include "actions/gravity.h"
#include "actions/collide.h"
#include "actions/shootit.h"
#include "actions/animate.h"

#include <stdio.h>

static int ACTIONS[ACTION_LIST_SIZE][ACTION_POOL_SIZE];

void Action_init() {
    int i, j;
    for (i = 0; i < ACTION_LIST_SIZE; ++i)
        for (j = 0; j < ACTION_POOL_SIZE; ++j)
            ACTIONS[i][j] = -1;
}

void Action_add(int POOL, int id) {
    int i, freepos = -1;
    for (i = 0; i < ACTION_POOL_SIZE; ++i) {
        /* Action pool already has this entity */
        if (ACTIONS[POOL][i] == id) return;

        /* Found a free position in the action pool */
        if (freepos == -1 && ACTIONS[POOL][i] == -1) {
            freepos = i;
            logprint("Adding action of type #%d to entity of id #%d\n", POOL, freepos);
        }
    }
    if (freepos == -1) {
        GAME_ERROR("Action pool is full.");
        return;
    }
    ACTIONS[POOL][freepos] = id;
}

void Action_remove(int POOL, int id) {
    int i;
    for (i = 0; i < ACTION_POOL_SIZE; ++i)
        if (ACTIONS[POOL][i] == id)
            ACTIONS[POOL][i] = -1;
}

void Action_update() {
    TurnLft( ACTIONS[ACTION_TURNLFT] );
    TurnRgt( ACTIONS[ACTION_TURNRGT] );
    MoveFwd( ACTIONS[ACTION_MOVEFWD] );
    AutoDie( ACTIONS[ACTION_AUTODIE] );
    Gravity( ACTIONS[ACTION_GRAVITY] );
    Collide( ACTIONS[ACTION_COLLIDE] );
    ShootIt( ACTIONS[ACTION_SHOOTIT] );
    Animate( ACTIONS[ACTION_ANIMATE] );
}
