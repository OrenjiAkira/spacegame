#ifndef GAME_FACTORY_H
#define GAME_FACTORY_H

void Factory_loadPlanet();
/* () -> void
Cria planeta central a partir das informações do arquivo de configuração. */

void Factory_loadPlayer1();
/* () -> void
Cria player 1 a partir das informações do arquivo de configuração. */

void Factory_loadPlayer2();
/* () -> void
Cria player 2 a partir das informações do arquivo de configuração. */

void Factory_loadBackground();
/* () -> void
Cria imagem de fundo. */

void Factory_newBullet(int origin_body, float m, float r, float lt);
/* () -> void
Cria uma bullet a partir do corpo físico de alguma entidade.
Carrega as especificações da bullet a partir das informações
do arquivo de configuração. */

void Factory_newExplosion(int origin_body);
/* () -> void
Cria uma explosão a partir do corpo físico de alguma entidade. */


#endif
