
#include "utility/macros.h"
#include "utility/entity.h"
#include "entities/picture.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static Entity *PICTURES[PICTURE_POOL_SIZE];

void Picture_init() {
    int id;
    for (id = 0; id < PICTURE_POOL_SIZE; ++id)
        PICTURES[id] = NULL;
}

int Picture_new(int drawpos, int sprite) {
    int id;

    for (id = 0; id < PICTURE_POOL_SIZE; ++id) {
        if (PICTURES[id] == NULL) {
            /* Alocar memória */
            PICTURES[id] = (Entity*)malloc( sizeof(Entity) );

            /* Definir componentes pelos parâmetros */
            PICTURES[id]->sprite = sprite;
            PICTURES[id]->drawpos = drawpos;

            /* Componentes não utilizados nunca */
            PICTURES[id]->drawquad = 
                PICTURES[id]->physics = 
                PICTURES[id]->timer_1 = 
                PICTURES[id]->timer_2 = 
                PICTURES[id]->textbox = -1;
            return id;
        }
    }
    pool_overflow(Picture);
}

void Picture_update() {

}

void Picture_destroy(int id) {
    if (PICTURES[id] != NULL) {
        free(PICTURES[id]);
        PICTURES[id] = NULL;
    }
}


void Picture_close() {
    int id;
    for (id = 0; id < PICTURE_POOL_SIZE; ++id) {
        Picture_destroy(id);
    }
}
