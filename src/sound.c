
#include "debug.h"
#include "game.h"
#include "sound.h"
#include "config/path.h"
#include "utility/string.h"

#include <SDL_mixer.h>

static char FX_FILENAMES[FX_TOTAL][16];
static Mix_Chunk *FX[FX_TOTAL];
static Mix_Music *ST = NULL;

static void load_error(char* str) {
    logprint("\"%s\" could not be loaded.\n", str);
    Game_quit();
}

static void play_error(char* str) {
    logprint("\"%s\" could not be played.\n", str);
}

void Sound_init() {
    char filepath[128];
    int i;

    String_join(FX_FILENAMES[FX_SELECT], "select.wav", "\0");
    String_join(FX_FILENAMES[FX_SHOOT], "laser.wav", "\0");
    String_join(FX_FILENAMES[FX_EXPLODE], "explosion.wav", "\0");

    for (i = 0; i < FX_TOTAL; ++i) {
        String_join(filepath, Path_toFX(), FX_FILENAMES[i]);
        if ( (FX[i] = Mix_LoadWAV(filepath)) == NULL ) load_error(filepath);
    }
}

void Sound_playSE(int fx_name) {
    if( Mix_PlayChannel( -1, FX[fx_name], 0 ) == -1 )
        play_error(FX_FILENAMES[fx_name]);
}

void Sound_close() {
    int i;

    /* Libera efeitos sonoros */
    for (i = 0; i < FX_TOTAL; ++i) {
        Mix_FreeChunk(FX[i]);
    }

    /* Libera música */
    if (ST != NULL) Mix_FreeMusic(ST);
}
