
#include "game.h"
#include "entity.h"
#include "action.h"
#include "components/physics.h"
#include "components/sprite.h"
#include "components/textbox.h"
#include "components/timer.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static Entity *ENTITIES[ENTITY_POOL_SIZE];

void Entity_init() {
    int id;
    for (id = 0; id < ENTITY_POOL_SIZE; ++id)
        ENTITIES[id] = NULL;
}

int Entity_new(int physics, int drawquad, int drawpos, int sprite, int textbox) {
    int id, t;

    for (id = 0; id < ENTITY_POOL_SIZE; ++id) {
        if (ENTITIES[id] == NULL) {
            /* Alocar memória */
            ENTITIES[id] = (Entity*)malloc( sizeof(Entity) );

            /* Definir componentes pelos parâmetros */
            ENTITIES[id]->physics = physics;
            ENTITIES[id]->sprite = sprite;
            ENTITIES[id]->drawpos = drawpos;
            ENTITIES[id]->drawquad = drawquad;
            ENTITIES[id]->textbox = textbox;

            /* Componentes inicialmente não utilizados */
            for (t = 0; t < TIMER_TYPES_TOTAL; ++t) ENTITIES[id]->timers[t] = -1;

            return id;
        }
    }
    POOL_OVERFLOW(Entity);
}

Entity* Entity_get(int id) {
    return ENTITIES[id];
}

void Entity_addTimer(int id, int timer_type, double secs) {
    VERIFY_ENTITY(id);
    ENTITIES[id]->timers[timer_type] = Timer_new(secs);
}

bool Entity_isTimerDone(int id, int timer_type) {
    if (id == -1 || ENTITIES[id] == NULL) return true; /* ??? Don't know what might happen */
    return Timer_isDone(ENTITIES[id]->timers[timer_type]);
}

void Entity_destroy(int id) {
    int a, t;
    if (id == -1 || ENTITIES[id] == NULL) return;

    for (a = 0; a < ACTION_LIST_SIZE; ++a) Action_remove(a, id);
    for (t = 0; t < TIMER_TYPES_TOTAL; ++t) Timer_kill(ENTITIES[id]->timers[t]);
    Physics_kill(ENTITIES[id]->physics);
    Sprite_kill(ENTITIES[id]->sprite);
    Textbox_kill(ENTITIES[id]->textbox);
    free(ENTITIES[id]);
    ENTITIES[id] = NULL;
}

void Entity_close() {
    int id;
    for (id = 0; id < ENTITY_POOL_SIZE; ++id) Entity_destroy(id);
}
