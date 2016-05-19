
#include "utility/macros.h"
#include "utility/entity.h"
#include "components/drawquad.h"
#include "components/physics.h"
#include "components/timer.h"
#include "entities/ship.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static Entity *SHIPS[SHIP_POOL_SIZE];

void Ship_init() {
    int id;
    for (id = 0; id < SHIP_POOL_SIZE; ++id)
        SHIPS[id] = NULL;
}

int Ship_new(int physics, int drawquad, int drawpos, int sprite, int textbox) {
    int id;

    for (id = 0; id < SHIP_POOL_SIZE; ++id) {
        if (SHIPS[id] == NULL) {
            /* Alocar memória */
            SHIPS[id] = (Entity*)malloc( sizeof(Entity) );

            /* Definir componentes pelos parâmetros */
            SHIPS[id]->physics = physics;
            SHIPS[id]->sprite = sprite;
            SHIPS[id]->drawpos = drawpos;
            SHIPS[id]->drawquad = drawquad;
            SHIPS[id]->textbox = textbox;

            /* Componentes inicialmente não utilizados */
            SHIPS[id]->timer_1 = SHIPS[id]->timer_2 = -1;
            
            return id;
        }
    }
    pool_overflow(Ship);
}

void Ship_update() {
    int id;

    for (id = 0; id < SHIP_POOL_SIZE; ++id) {
        if (SHIPS[id] != NULL) {
            Physics_gravitate(SHIPS[id]->physics);
            Physics_print(SHIPS[id]->physics);
        }
    }
}

void Ship_destroy(int id) {
    if (SHIPS[id] != NULL) {
        free(SHIPS[id]);
        SHIPS[id] = NULL;
    }
}

void Ship_close() {
    int id;
    for (id = 0; id < SHIP_POOL_SIZE; ++id) {
        Ship_destroy(id);
    }
}

void Ship_accelerate(int id) {
    if (SHIPS[id] == NULL) return;
    Physics_accelerate(SHIPS[id]->physics);
}

void Ship_turnLeft(int id) {
    if (SHIPS[id] == NULL) return;
    if ( Timer_isDone(SHIPS[id]->timer_2) ) {
        Physics_changedir(SHIPS[id]->physics, -1);
        DrawQuad_next(SHIPS[id]->drawquad);
        SHIPS[id]->timer_2 = Timer_new(0.1);
    }
}

void Ship_turnRight(int id) {
    if (SHIPS[id] == NULL) return;
    if ( Timer_isDone(SHIPS[id]->timer_2) ) {
        Physics_changedir(SHIPS[id]->physics, 1);
        DrawQuad_prev(SHIPS[id]->drawquad);
        SHIPS[id]->timer_2 = Timer_new(0.1);
    }
}
