#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define GAME_ERROR(error) printf("ERROR: " #error "\n"); Game_quit()
#define POOL_OVERFLOW(type) GAME_ERROR(#type " pool overflow"); return 0

void Game_init(char *execpath);
/* () -> void
Inicializa todos os módulos do programa.
Em seguida carrega as instâncias e começa o jogo. */

void Game_setPlayer1(int id);
/* (int) -> void
Registra o ID da entidade que representa o player 1. */

void Game_setPlayer2(int id);
/* (int) -> void
Registra o ID da entidade que representa o player 2. */

int Game_getPlayer1();
/* () -> int
Retorna o ID da entidade que representa o player 1. */

int Game_getPlayer2();
/* () -> int
Retorna o ID da entidade que representa o player 2. */

bool Game_update();
/* () -> void
Atualiza a lógica do jogo, percorrendo todos os seus módulos em ordem.
Retorna um boolean que indica se o jogo deve encerrar (true significa
que o jogo vai terminar; false continua executando o programa normalmente). */

void Game_quit();
/* () -> void
Muda a flag de encerrar o jogo para true. Isso faz que a função Game_update()
retorne true e termine o programa de maneira correta. */

void Game_close();
/* () -> void
Encerra os módulos do programa e libera as memórias alocadas. */

#endif
