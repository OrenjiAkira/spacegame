
#include "utility/macros.h"
#include "utility/entity.h"
#include "components/drawquad.h"
#include "components/timer.h"
#include "entities/planet.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static Entity *PLANETS[PLANET_POOL_SIZE];

void Planet_init() {
    int id;
    for (id = 0; id < PLANET_POOL_SIZE; ++id)
        PLANETS[id] = NULL;
}

int Planet_new(int physics, int drawquad, int drawpos, int sprite) {
    int id;

    for (id = 0; id < PLANET_POOL_SIZE; ++id) {
        if (PLANETS[id] == NULL) {
            /* Alocar memória */
            PLANETS[id] = (Entity*)malloc( sizeof(Entity) );

            /* Definir componentes pelos parâmetros */
            PLANETS[id]->physics = physics;
            PLANETS[id]->sprite = sprite;
            PLANETS[id]->drawpos = drawpos;
            PLANETS[id]->drawquad = drawquad;

            /* Componentes inicialmente não utilizados */
            PLANETS[id]->timer_1 = PLANETS[id]->timer_2 = -1;
            
            /* Componentes não utilizados nunca */
            PLANETS[id]->textbox = -1;

            return id;
        }
    }
    pool_overflow(Planet);
}

void Planet_update() {
    int id;

    for (id = 0; id < PLANET_POOL_SIZE; ++id) {
        if (PLANETS[id] != NULL) {
            if ( Timer_isDone(PLANETS[id]->timer_1) ) {
                DrawQuad_next(PLANETS[id]->drawquad);
                PLANETS[id]->timer_1 = Timer_new(1.0/10);
                printf("CHANGE QUAD!\n");
            }
        }
    }
}

void Planet_destroy(int id) {
    if (PLANETS[id] != NULL) {
        free(PLANETS[id]);
        PLANETS[id] = NULL;
    }
}

void Planet_close() {
    int id;
    for (id = 0; id < PLANET_POOL_SIZE; ++id) {
        Planet_destroy(id);
    }
}

