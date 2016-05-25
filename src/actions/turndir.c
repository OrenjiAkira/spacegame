
#include "entity.h"
#include "action.h"
#include "components/physics.h"
#include "components/drawquad.h"
#include "components/timer.h"
#include "actions/turndir.h"

#include <stdio.h>
#include <stdlib.h>

void TurnRgt(int *POOL) {
    Entity *entity;
    FOREACH_VALID_ENTITY(POOL) {
        GET_ENTITY(ACTION_TURNRGT);
        Physics_changedir(entity->physics, 1);
        DrawQuad_prev(entity->drawquad);
        printf("\n\nENTITY ID: #%d\n\n", POOL[i]);
        Action_remove(ACTION_TURNRGT, POOL[i]);
    }
}

void TurnLft(int *POOL) {
    Entity *entity;
    FOREACH_VALID_ENTITY(POOL) {
        GET_ENTITY(ACTION_TURNLFT);
        Physics_changedir(entity->physics, -1);
        DrawQuad_next(entity->drawquad);
        printf("\n\nENTITY ID: #%d\n\n", POOL[i]);
        Action_remove(ACTION_TURNLFT, POOL[i]);
    }
}
