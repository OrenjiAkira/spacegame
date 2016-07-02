#ifndef GAME_GAMEPLAY_H
#define GAME_GAMEPLAY_H

void GamePlay_load();
/* () -> void
Carrega as entidades da cena de gameplay do jogo (imagem de fundo, planeta, naves). */

void GamePlay_pause();
/* () -> void
 */

void GamePlay_unpause();
/* () -> void
 */

void GamePlay_close();
/* () -> void
Encerra e libera memória das entidades da cena de gameplay. */

void GamePlay_setPlayer1(int id);
/* (int) -> void
Registra o ID da entidade que representa o player 1. */

void GamePlay_setPlayer2(int id);
/* (int) -> void
Registra o ID da entidade que representa o player 2. */

int GamePlay_getPlayer1();
/* () -> int
Retorna o ID da entidade que representa o player 1. */

int GamePlay_getPlayer2();
/* () -> int
Retorna o ID da entidade que representa o player 2. */

void GamePlay_newBullet(int origin_body, float m, float r, float lt);
/* () -> void
Cria uma bullet a partir do corpo físico de alguma entidade.
Carrega as especificações da bullet a partir das informações
do arquivo de configuração. */

void GamePlay_newExplosion(int origin_body);
/* () -> void
Cria uma explosão a partir do corpo físico de alguma entidade. */

#endif
