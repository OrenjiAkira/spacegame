#ifndef GAME_DRAWPOS_H
#define GAME_DRAWPOS_H

#include "utility/entity.h"
#include "utility/vector.h"

#include <SDL.h>

#define DRAWPOS_POOL_SIZE ENTITY_POOL_SIZE

typedef struct _drawpos DrawPos;
/* DrawPos
Struct de posições. Guarda informação sobre a posição
de renderização de uma entidade. */

void DrawPos_init();
/* () -> void
Inicializa pool de DrawPos. */

int DrawPos_new(int body_id, int qw, int qh, float ox, float oy);
/* (int, int, int, float, float) -> int
Cria um novo DrawPos e retorna o seu id. */

void DrawPos_kill(int id);
/* (int) -> void
Destrói um DrawPos  */

void DrawPos_update();
/* (int) -> void
Atualiza a posição de uma entidade. */

SDL_Rect* DrawPos_getPos(int id);
/* (int) -> SDL_Rect*
Retorna o quad ativo de um DrawPos. */

Vector* DrawPos_getOffset(int id);
/* (int) -> Vector*
Retorna o offset de um DrawPos. */

#endif
