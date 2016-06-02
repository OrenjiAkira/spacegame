#ifndef GAME_DIRECTIONS_H
#define GAME_DIRECTIONS_H

#include "utility/vector.h"

#define DIRECTION_POOL_SIZE 12
#define PI 3.1415926535898

void Direction_init();
/* () -> void
Cria todas as direções existentes e utilizáveis no jogo. */

Vector* Direction_getVector(int id);
/* (int) -> Vector*
Recebe o id de uma direção, e retorna seu vetor normalizado (de magnitude 1). */

#endif
