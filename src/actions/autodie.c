
#include "entity.h"
#include "action.h"
#include "components/physics.h"
#include "components/timer.h"
#include "actions/autodie.h"

#include <stdio.h>
#include <stdlib.h>

void AutoDie(int *POOL) {
    Entity *entity;
    int i;
    for (i = 0; i < ENTITY_POOL_SIZE; ++i) {
        if (POOL[i] != -1) {
            if ( (entity = Entity_get(POOL[i])) == NULL ){
                Action_remove(ACTION_AUTODIE, POOL[i]);
                return;
            }
            if ( entity->timer_2 != -1 && Timer_isDone(entity->timer_2) ) {
                printf("BOOM YOU ARE DEAD\n");
                Entity_destroy(POOL[i]);
                Action_remove(ACTION_AUTODIE, POOL[i]);
            }
        }
    }   
}
