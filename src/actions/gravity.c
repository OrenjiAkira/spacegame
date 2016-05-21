
#include "entity.h"
#include "action.h"
#include "components/physics.h"
#include "actions/gravity.h"

#include <stdio.h>
#include <stdlib.h>

void Gravity(int *POOL) {
    Entity *entity;
    int i;
    for (i = 0; i < ENTITY_POOL_SIZE; ++i) {
        if (POOL[i] != -1) {
            if ( (entity = Entity_get(POOL[i])) == NULL ){
                Action_remove(ACTION_GRAVITY, POOL[i]);
                return;
            }
            Physics_gravitate(entity->physics);
            Physics_print(entity->physics);
        }
    }
}


