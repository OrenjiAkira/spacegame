
#include "entity.h"
#include "action.h"
#include "components/physics.h"
#include "actions/movefwd.h"


#include <stdlib.h>

void MoveFwd(int *POOL) {
    Entity *entity;
    FOREACH_VALID_ENTITY(POOL) {
        GET_ENTITY(ACTION_MOVEFWD);
        Physics_accelerate(entity->physics);
        Action_remove(ACTION_MOVEFWD, POOL[i]);
    }
}
