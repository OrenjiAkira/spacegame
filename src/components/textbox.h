#ifndef GAME_TEXTBOX_H
#define GAME_TEXTBOX_H

#include "entity.h"

#define TEXTBOX_POOL_SIZE ENTITY_POOL_SIZE

typedef struct _textbox Textbox;
/* Textbox
Struct de caixa de texto. Entidades que possuem
algum texto usam esse componente para se desenhá-lo. */

enum _textalign {
    TEXTALIGN_LEFT,
    TEXTALIGN_CENTER,
    TEXTALIGN_RIGHT
};

void Textbox_init();
/* () -> void
Inicializa pool de textbox */

int Textbox_new(char* text, int dpos_id, int align, int size, int color);
/* (char*, int, int, int, int) -> int
Cria um textbox e retorna seu id. Recebe o texto a ser desenhado,
um id de drawpos, um índice de alinhamento de texto (declarado
acima no enum), um índice de tamanho fonte, e outro de cor,
ambos declarados em "config/font.c". */

void Textbox_kill(int id);
/* (int) -> void
Libera o espaço de um textbox. */

void Textbox_update();
/* () -> void
Desenha os textbox ativos da pool. */

void Textbox_hide(int id);
/* (int) -> void
Faz o textbox não ser desenhado no update.
O padrão é ser desenhado. */

void Textbox_show(int id);
/* (int) -> void
Faz o textbox ser desenhado no update.
O padrão é ser desenhado. */

void Textbox_close();
/* () -> void
Libera a pool inteira, destruindo textbox ativos. */

#endif
