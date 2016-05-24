
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

static int ACTIONS[ACTION_LIST_SIZE][ENTITY_POOL_SIZE];

void Action_init() {
    int i, j;
    for (i = 0; i < ACTION_LIST_SIZE; ++i)
        for (j = 0; j < ENTITY_POOL_SIZE; ++j)
            ACTIONS[i][j] = -1;
}

void Action_add(int POOL, int id) {
    int i, free = -1;
    for (i = 0; i < ENTITY_POOL_SIZE; ++i) {
        if (ACTIONS[POOL][i] == id) return;
        if (free == -1 && ACTIONS[POOL][i] == -1) free = i;
    }
    ACTIONS[POOL][free] = id;
}

void Action_remove(int POOL, int id) {
    int i;
    for (i = 0; i < ENTITY_POOL_SIZE; ++i)
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

