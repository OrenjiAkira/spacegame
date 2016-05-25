
#include "entity.h"
#include "action.h"
#include "components/drawquad.h"
#include "components/timer.h"
#include "actions/animate.h"

#include <stdlib.h>

void Animate(int *POOL) {
    Entity *entity;
    FOREACH_VALID_ENTITY(POOL) {
        GET_ENTITY(ACTION_ANIMATE);
        if ( Timer_isDone(entity->timers[TIMER_ANIMATION]) ) {
            DrawQuad_next(entity->drawquad);
            Entity_addTimer(POOL[i], TIMER_ANIMATION, 0.1);
        }
    }   
}
