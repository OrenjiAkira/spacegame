
#include "entity.h"
#include "action.h"
#include "utility/macros.h"
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
    int id;

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
            ENTITIES[id]->timer_1 = ENTITIES[id]->timer_2 = -1;

            return id;
        }
    }
    pool_overflow(Entity);
}

Entity* Entity_get(int id) {
    return ENTITIES[id];
}

void Entity_destroy(int id) {
    int a;
    if (ENTITIES[id] != NULL) {
        for (a = 0; a < ACTION_LIST_SIZE; ++a) Action_remove(a, id);
        Physics_kill(ENTITIES[id]->physics);
        Sprite_kill(ENTITIES[id]->sprite);
        Textbox_kill(ENTITIES[id]->textbox);
        Timer_kill(ENTITIES[id]->timer_1);
        Timer_kill(ENTITIES[id]->timer_2);
        free(ENTITIES[id]);
        ENTITIES[id] = NULL;
    }
}

void Entity_close() {
    int id;
    for (id = 0; id < ENTITY_POOL_SIZE; ++id) {
        Entity_destroy(id);
    }
}




