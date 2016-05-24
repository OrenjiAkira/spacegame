#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#include "entity.h"
#include "utility/vector.h"

#include <stdbool.h>

#define GCONST 6.67e-11
#define SPEEDLIMIT 0.5
#define ACC 0.005

#define PHYSICS_POOL_SIZE ENTITY_POOL_SIZE

typedef struct _physics Physics;
/* Physics
Struct de física. Todo elemento
que usa uma posição no jogo contém
uma instância deste struct. */

void Physics_init();
/* () -> void
Inicializa pool de physics. */

int Physics_new(float m, float r, float x, float y, float vx, float vy);
/* (float, float, float, float, float, float) -> int
Cria um novo corpo físico e devolve seu id. */

void Physics_update();
/* () -> void 
Atualiza a posição e velocidade de todos os corpos físicos. */

Vector* Physics_getPos(int id);
/* (int) -> Vector*
Retorna a posição de um corpo físico. */

int Physics_getDirection(int id);
/* (int) -> Vector*
Retorna o índice da direção de um corpo físico. */

void Physics_kill(int id);
/* (int) -> void
Destrói um corpo físico. */

void Physics_gravitate(int id);
/* (int) -> void
Calcula a atração gravitacional entre um corpo
e todos os outros existentes. Adiciona a aceleração
vetorial calculada na velocidade. Apenas a velocidade
do corpo cujo id é passado como parâmetro é modificada. */

bool Physics_isColliding(int id);
/* (int) -> bool
Retorna true se o checkCollision() achou alguma
colisão. Retorna false se não. */

void Physics_checkCollision(int id);
/* (int) -> void
Verifica colisões. Se houver alguma, aciona
a bool de colisão na struct de física. */

void Physics_accelerate(int id);
/* (int, int) -> void
Propulsiona um corpo físico. */

void Physics_changedir(int id, int dir);
/* (int, int) -> void
Muda a direção de propulsão um corpo físico. */

void Physics_print(int id);
/* (int) -> void
Imprime os parâmetros de um corpo físico. */

#endif
