
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
        if ( Timer_isDone(entity->timer_1) ) {
            DrawQuad_next(entity->drawquad);
            entity->timer_1 = Timer_new(1.0/10);
        }
    }   
}
