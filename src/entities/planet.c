
#include "utility/macros.h"
#include "utility/entity.h"
#include "components/timer.h"
#include "entities/planet.h"

static Entity *PLANETS[PLANET_POOL_SIZE];

void Planet_init() {
    int id;
    for (id = 0; i < PLANET_POOL_SIZE; ++id)
        PLANETS[id] = NULL;
}

int Planet_new(int physics, int drawpos, int sprite, int quad) {
    Entity* planet;
    int id;

    foreach(PLANETS, Entity*, id, planet) {
        if (planet == NULL) {
            /* Alocar memória */
            planet = (Entity*)malloc( sizeof(Entity) );

            /* Definir componentes pelos parâmetros */
            planet->physics = physics;
            planet->sprite = sprite;
            planet->drawpos = drawpos;

            /* Definir componentes iniciais */
            planet->drawquad = quad;
            planet->timer_1 = planet->timer_2 = TIMER_FREE;
            
            /* componentes não utilizados */
            planet->direction = PLANETS[id]->textbox = -1;

            return id;
        }
    }
    pool_overflow(Planet);
}

void Planet_update() {
    Entity* planet;
    int id;

    foreach(PLANETS, Entity*, id, planet) {
        if (planet != NULL) {
            if ( Timer_done(planet->timer_1) ) {
                DrawQuad_next(planet->drawquad);
                planet->timer_1 = Timer_new(12);
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
    for (id = 0; i < PLANET_POOL_SIZE; ++id) {
        Planet_destroy(id);
    }
}

