
#include "entity.h"
#include "action.h"
#include "factory.h"
#include "components/physics.h"
#include "actions/collide.h"


#include <stdlib.h>

void Collide(int *POOL) {
    Entity *entity;
    FOREACH_VALID_ENTITY(POOL) {
        GET_ENTITY(ACTION_COLLIDE);
        if ( Physics_isColliding(entity->physics) ) {
            Factory_newExplosion(entity->physics);
            Entity_destroy(POOL[i]);
            Action_remove(ACTION_COLLIDE, POOL[i]);
            return;
        }
        Physics_checkCollision(entity->physics);
    }   
}
