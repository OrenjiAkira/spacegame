#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "utility/entity.h"

#define SPRITE_POOL_SIZE ENTITY_POOL_SIZE
#define LAYER_COUNT 4

typedef struct _sprite Sprite;
/* Sprite
 */


void Sprite_init();
/* () -> void
 */

int Sprite_new(char* filename, int dpos_id, int dquad_id, int layer);
/* (char*, int, int) -> void
 */

void Sprite_kill(int id);
/* (int) -> void
 */

void Sprite_update();
/* () -> void
 */

void Sprite_close();
/* () -> void
 */


#endif
