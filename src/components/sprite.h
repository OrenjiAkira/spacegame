#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "entity.h"

#define SPRITE_POOL_SIZE ENTITY_POOL_SIZE

typedef struct _sprite Sprite;
/* Sprite
Struct de sprite. Entidades que possuem
uma imagem que a representa visualmente
na tela usam esse componente para se desenhar. */

enum _layers {
    LAYER_BACKGROUND,
    LAYER_MIDGROUND1,
    LAYER_MIDGROUND2,
    LAYER_FOREGROUND,
    LAYER_COUNT
};

void Sprite_init();
/* () -> void
Inicializa pool de sprites */

int Sprite_new(char* filename, int dpos_id, int dquad_id, int layer);
/* (char*, int, int, int) -> void
Cria um sprite novo na pool de sprites e retorna seu id.
Recebe o nome do arquivo de imagem, um id de drawpos,
um id de drawquad, e a layer a qual pertence. */

void Sprite_kill(int id);
/* (int) -> void
Libera o espaço de um sprite. */

void Sprite_update();
/* () -> void
Desenha os sprites existentes na pool. */

void Sprite_close();
/* () -> void
Libera a pool inteira, destruindo sprites ativos. */

#endif
