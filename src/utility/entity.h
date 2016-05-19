#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#define ENTITY_POOL_SIZE 128

typedef struct _entity {
    int physics;
    int sprite;
    int textbox;
    int drawpos;
    int drawquad;
    int timer_1;
    int timer_2;
} Entity;

/* Entity
Uma struct básica que pode
armazenar vários componentes. */

/* Components available:
int physics;
int drawpos;
int sprite;
int quad;
int textbox;
int direction;
int timer_1;
int timer_2;
*/

#endif
