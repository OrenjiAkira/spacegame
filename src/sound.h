#ifndef GAME_SOUND_H
#define GAME_SOUND_H

enum _fx_list {
    FX_SELECT,
    FX_SHOOT,
    FX_EXPLODE,
    FX_TOTAL
};

void Sound_init();
/* () -> void */

void Sound_playSE(int fx_name);
/* (int) -> void */

void Sound_close();
/* () -> void */


#endif
