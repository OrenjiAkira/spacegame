#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <stdbool.h>

#define ENTITY_POOL_SIZE 128

#define VERIFY_ENTITY(id) if (ENTITIES[id] == NULL) { printf("INVALID ENTITY ID #%d. ENTITY IS NOT ACTIVE.\n", id); return; }

enum _timer_types {
    TIMER_INPUTDELAY1,
    TIMER_INPUTDELAY2,
    TIMER_COUNTDOWN1,
    TIMER_COUNTDOWN2,
    TIMER_ANIMATION,
    TIMER_TYPES_TOTAL
};

typedef struct _entity {
    int physics;
    int drawpos;
    int drawquad;
    int sprite;
    int textbox;
    int timers[TIMER_TYPES_TOTAL];
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

void Entity_addTimer(int id, int timer_type, double secs);

bool Entity_isTimerDone(int id, int timer_type);

void Entity_destroy(int id);

void Entity_close();

#endif
