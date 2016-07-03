#ifndef GAME_GLOBALS_H
#define GAME_GLOBALS_H

enum _globals_ids {
    GLOBAL_P1CAT,
    GLOBAL_P2CAT,
    GLOBAL_P1SCORE,
    GLOBAL_P2SCORE,
    GLOBAL_TOTAL
};

void Globals_init();
/* () -> void
 */

int Globals_get(int global_id);
/* (int) -> int
Retorna a global requisitada, se ela existir.
Se não existir, o jogo fecha. */

#endif
