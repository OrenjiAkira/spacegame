
#include "entity.h"
#include "action.h"
#include "components/physics.h"
#include "components/timer.h"
#include "actions/autodie.h"

#include <stdlib.h>

void AutoDie(int *POOL) {
    Entity *entity;
    FOREACH_VALID_ENTITY(POOL) {
        GET_ENTITY(ACTION_AUTODIE);
        if ( entity->timer_2 != -1 && Timer_isDone(entity->timer_2) ) {
            Entity_destroy(POOL[i]);
            Action_remove(ACTION_AUTODIE, POOL[i]);
        }
    }   
}
