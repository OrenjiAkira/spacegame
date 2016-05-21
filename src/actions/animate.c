
#include "entity.h"
#include "action.h"
#include "components/drawquad.h"
#include "components/timer.h"
#include "actions/animate.h"

#include <stdlib.h>

void Animate(int *POOL) {
    Entity *entity;
    int i;
    for (i = 0; i < ENTITY_POOL_SIZE; ++i) {
        if (POOL[i] != -1) {
            if ( (entity = Entity_get(POOL[i])) == NULL ){
                Action_remove(ACTION_ANIMATE, POOL[i]);
                return;
            }
            if ( Timer_isDone(entity->timer_1) ) {
                DrawQuad_next(entity->drawquad);
                entity->timer_1 = Timer_new(1.0/10);
            }
        }
    }   
}




