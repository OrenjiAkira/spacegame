
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
        if ( entity->timers[TIMER_COUNTDOWN1] != -1 && Entity_isTimerDone(POOL[i], TIMER_COUNTDOWN1) ) {
            Entity_destroy(POOL[i]);
            Action_remove(ACTION_AUTODIE, POOL[i]);
        }
    }   
}
