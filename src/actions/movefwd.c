
#include "entity.h"
#include "action.h"
#include "components/physics.h"
#include "actions/movefwd.h"

#include <stdlib.h>

void MoveFwd(int *POOL) {
    Entity *entity;
    int i;
    for (i = 0; i < ENTITY_POOL_SIZE; ++i) {
        if (POOL[i] != -1) {
            if ( (entity = Entity_get(POOL[i])) == NULL ) {
                Action_remove(ACTION_MOVEFWD, POOL[i]);
                return;
            }
            Physics_accelerate(entity->physics);
            Action_remove(ACTION_MOVEFWD, POOL[i]);
        }
    }
}
