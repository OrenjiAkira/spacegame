#ifndef GAME_TEXTBOX_H
#define GAME_TEXTBOX_H

#include "entity.h"

#define TEXTBOX_POOL_SIZE ENTITY_POOL_SIZE

typedef struct _textbox Textbox;

enum _textalign {
    TEXTALIGN_LEFT,
    TEXTALIGN_CENTER,
    TEXTALIGN_RIGHT
};

void Textbox_init();
/* () -> void
 */

int Textbox_new(char* text, int dpos_id, int align, int size, int color);
/* (char*, int, int, int) -> int
 */

void Textbox_kill(int id);
/* (int) -> void
 */

void Textbox_update();
/* () -> void
 */

void Textbox_close();
/* () -> void
 */


#endif
