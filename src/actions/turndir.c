
#include "entity.h"
#include "action.h"
#include "components/physics.h"
#include "components/drawquad.h"
#include "components/timer.h"
#include "actions/turndir.h"

#include <stdlib.h>

void TurnRgt(int *POOL) {
    Entity *entity;
    FOREACH_VALID_ENTITY(POOL) {
        GET_ENTITY(ACTION_TURNRGT);
        if ( Timer_isDone(entity->timer_2) ) {
            Physics_changedir(entity->physics, 1);
            DrawQuad_prev(entity->drawquad);
            Action_remove(ACTION_TURNRGT, POOL[i]);
            entity->timer_2 = Timer_new(0.1);
        }
    }
}

void TurnLft(int *POOL) {
    Entity *entity;
    FOREACH_VALID_ENTITY(POOL) {
        GET_ENTITY(ACTION_TURNLFT);
        if ( Timer_isDone(entity->timer_2) ) {
            Physics_changedir(entity->physics, -1);
            DrawQuad_next(entity->drawquad);
            Action_remove(ACTION_TURNLFT, POOL[i]);
            entity->timer_2 = Timer_new(0.1);
        }
    }
}
