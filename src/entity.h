#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#define ENTITY_POOL_SIZE 128

typedef struct _entity {
    int physics;
    int drawpos;
    int drawquad;
    int sprite;
    int textbox;
    int timer_1;
    int timer_2;
} Entity;

/* Entity
Uma struct básica que pode
armazenar vários componentes. */

/* Componentes disponíveis:
    int physics;
    int drawpos;
    int drawquad;
    int sprite;
    int textbox;
    int timer_1;
    int timer_2; */

void Entity_init();

int Entity_new(int physics, int drawquad, int drawpos, int sprite, int textbox);

Entity* Entity_get(int id);

void Entity_destroy(int id);

void Entity_close();

#endif
