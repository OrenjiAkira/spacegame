
#include "entity.h"
#include "action.h"
#include "components/physics.h"
#include "actions/gravity.h"


#include <stdlib.h>

void Gravity(int *POOL) {
    Entity *entity;
    FOREACH_VALID_ENTITY(POOL) {
        GET_ENTITY(ACTION_GRAVITY);
        Physics_gravitate(entity->physics);
        Physics_print(entity->physics);
    }
}
