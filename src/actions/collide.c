
#include "entity.h"
#include "action.h"
#include "components/physics.h"
#include "actions/collide.h"

#include <stdio.h>
#include <stdlib.h>

void Collide(int *POOL) {
    Entity *entity;
    int i;
    for (i = 0; i < ENTITY_POOL_SIZE; ++i) {
        if (POOL[i] != -1) {
            if ( (entity = Entity_get(POOL[i])) == NULL ){
                Action_remove(ACTION_COLLIDE, POOL[i]);
                return;
            }
            if ( Physics_isColliding(entity->physics) ) {
                printf("COLLISION! BOOM YOU ARE DEAD\n");
                Entity_destroy(POOL[i]);
                Action_remove(ACTION_COLLIDE, POOL[i]);
                return;
            }
            Physics_checkCollision(entity->physics);
        }
    }   
}

