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
Retorna uma string de configuração
de uma seção especificada. */

void Conf_getFramerateValue(int* f);
/* () -> void
Recebe um ponteiro de inteiro e modifica
o valor apontado para o FPS definido
no arquivo de configuração. */

void Conf_getMapValues(float* w, float* h);
/* () -> void
Recebe ponteiros de floats e os modifica
para apontarem para o valor das dimensões
do mundo no arquivo de configuração. */

void Conf_getPlanetValues(float* m, float* r, float* x, float* y);
/* () -> void
Recebe ponteiros de floats e os modifica
para apontarem para os valores do corpo físico
do planeta existentes no arquivo de configuração. */

void Conf_getShipValues(int ship, char* name, float* m, float* r, float* x, float* y, float* vx, float* vy);
/* () -> void
Recebe ponteiros de floats, um ponteiro de char
e um inteiro. Modifica os ponteiros para apontarem
para os valores da nave (especificada pelo inteiro)
existentes no arquivo de configuração. */

void Conf_getBulletValues(float* m, float* r, float* lifetime);
/* () -> void
Recebe ponteiros de floats e os modifica
para apontarem para os valores das bullets
existentes no arquivo de configuração. */

/* NOTE TO SELF:
O arquivo de configuração deveria especificar o nome dos arquivos de imagem
carregados pelo jogo para representar os seus elementos visuais. Essas funções
acima deveriam ser modificadas para pegarem esse valor também. */

#endif
