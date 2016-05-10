#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <stdbool.h>

#define ENTITY_POOL_SIZE 128

typedef struct _entity Entity;
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
