#ifndef GAME_TIMER_H
#define GAME_TIMER_H

#include "entity.h"

#include <stdbool.h>

#define TIMER_POOL_SIZE TIMER_TYPES_TOTAL*ENTITY_POOL_SIZE

typedef struct _timer Timer;
/* Timer
Struct de temporizador. Guarda um counter
para realizar alguma ação que perdura tempo,
ou que acontece após um período de tempo. */

void Timer_init();
/* () -> void
Inicializa pool de timers. */

int Timer_new(double secs);
/* (int) -> int
Cria um novo timer e devolve seu id. */

void Timer_update();
/* () -> int
Avança cada um dos timers. */

void Timer_kill(int id);
/* (int) -> void
Termina um timer mesmo que não tenha acabado. */

float Timer_progress(int id);
/* (int) -> float
Verifica o progresso do timer especificado.
Retorna um valor de 0 a 100 se o timer
estiver ativo; senão retorna -1. */

bool Timer_isDone(int id);
/* (int) -> bool
Retorna true se o timer especificado haver
terminado. Retorna false caso contrário. */

#endif
