
#include "entity.h"
#include "action.h"
#include "components/physics.h"
#include "actions/collide.h"
#include "scenes/gameplay.h"

#include <stdlib.h>

void Collide(int *POOL) {
    Entity *entity;
    FOREACH_VALID_ENTITY(POOL) {
        GET_ENTITY(ACTION_COLLIDE);
        if ( Physics_isColliding(entity->physics) ) {
            GamePlay_newExplosion(entity->physics);
            if (POOL[i] == GamePlay_getPlayer1()) GamePlay_setPlayer1(-1);
            if (POOL[i] == GamePlay_getPlayer2()) GamePlay_setPlayer2(-1);
            Entity_destroy(POOL[i]);
            Action_remove(ACTION_COLLIDE, POOL[i]);
            return;
        }
        Physics_checkCollision(entity->physics);
    }
}
