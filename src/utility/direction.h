#ifndef GAME_DIRECTIONS_H
#define GAME_DIRECTIONS_H

#include "utility/vector.h"

#define DIRECTION_POOL_SIZE 12

void Direction_init();

Vector* Direction_getVector(int id);

#endif
