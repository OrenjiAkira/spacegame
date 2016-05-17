#ifndef GAME_CONF_H
#define GAME_CONF_H

enum _config {
    CONF_FRAMERATE,
    CONF_MAP,
    CONF_PLANET,
    CONF_SHIP1,
    CONF_SHIP2,
    CONF_BULLETS,
    CONF_LENGTH
};

void Conf_init();
/* () -> void
Lê o arquivo de configuração e
guarda strings de leitura em um vetor. */

char* Conf_get(int section_name);
/* (int) -> char*
Devolve uma string de configuração
de uma seção especificada. */

#endif
