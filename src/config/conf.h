#ifndef GAME_CONF_H
#define GAME_CONF_H

#define BUFFER_SIZE 128

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

char* Conf_getString(int section_name);
/* (int) -> char*
Devolve uma string de configuração
de uma seção especificada. */

void Conf_getFramerateValue(int* f);
/* () -> void
 */

void Conf_getMapValues(float* w, float* h);
/* () -> void
 */

void Conf_getPlanetValues(float* m, float* r, float* x, float* y);
/* () -> void
 */

void Conf_getShipValues(int ship, char* name, float* m, float* r, float* x, float* y, float* vx, float* vy);
/* () -> void
 */

void Conf_getBulletValues(float* m, float* r, float* lifetime);
/* () -> void
 */


#endif
