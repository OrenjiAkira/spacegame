#ifndef GAME_MAP_H
#define GAME_MAP_H

typedef struct _map Map;
/* Map
Struct de mapa. Armazena as informações de dimensão do mapa do jogo. */

void Map_init();
/* () -> void
Inicializa os valores do mapa. */

float Map_getWidth();
/* () -> float
Retorna o valor da dimensão horizontal do mapa. */

float Map_getHeight();
/* () -> float
Retorna o valor da dimensão vertical do mapa. */

float Map_getUnitX();
/* () -> float
Retorna o valor da dimensão de uma unidade horizontal do mapa em pixels. */

float Map_getUnitY();
/* () -> float
Retorna o valor da dimensão de uma unidade vertical do mapa em pixels. */

#endif
