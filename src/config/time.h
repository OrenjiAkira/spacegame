#ifndef GAME_TIME_H
#define GAME_TIME_H

typedef struct _time Time;
/* Time
Struct de tempo. Armazena informações de tempo
da execução do programa, como seu framerate e
o tamanho de um frame em milisegundos. */

void Time_init();
/* () -> void
Inicializa e carrega os valores de tempo do jogo.
São eles o framerate, o frameunit, e o framems. */

double Time_getFrameunit();
/* () -> double
Retorna o tempo em segundos de um frame do jogo. */

int Time_getFramerate();
/* () -> int
Retorna o número de frames em um segundo de jogo. */

int Time_getFramemilisec();
/* () -> int
Retorna o tempo em milisegundos de um frame do jogo. */

#endif
