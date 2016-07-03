
#include "debug.h"
#include "game.h"
#include "sound.h"
#include "config/path.h"
#include "utility/string.h"

#include <SDL_mixer.h>

static char FX_FILENAMES[FX_TOTAL][16];
static char BGM_PATH[16];

static Mix_Chunk *FX[FX_TOTAL];
static Mix_Music *BGM = NULL;

static void load_error(char* str) {
    logprint("\"%s\" could not be loaded. %s\n", str, Mix_GetError());
    Game_quit();
}

static void play_error(char* str) {
    logprint("\"%s\" could not be played.\n", str);
}

void Sound_init() {
    char filepath[128];
    int i;

    String_join(FX_FILENAMES[FX_SELECT], "select.wav", "\0");
    String_join(FX_FILENAMES[FX_MARU], "ok.wav", "\0");
    String_join(FX_FILENAMES[FX_BATSU], "no.wav", "\0");
    String_join(FX_FILENAMES[FX_SHOOT], "laser.wav", "\0");
    String_join(FX_FILENAMES[FX_EXPLODE], "explosion.wav", "\0");
    String_join(FX_FILENAMES[FX_EXPLODE], "explosion.wav", "\0");
    String_join(BGM_PATH, "space_menu.mp3", "\0");

    /* Inicializando SE */
    for (i = 0; i < FX_TOTAL; ++i) {
        String_join(filepath, Path_toFX(), FX_FILENAMES[i]);
        if ( (FX[i] = Mix_LoadWAV(filepath)) == NULL ) load_error(filepath);
    }

    /* Inicializando BGM */
    String_join(filepath, Path_toBGM(), BGM_PATH);
    logprint("Loading bgm from file: '%s'...\n", filepath);
    if ( (BGM = Mix_LoadMUS(filepath)) == NULL ) load_error(filepath);

}

void Sound_playSE(int fx_name) {
    if( Mix_PlayChannel( -1, FX[fx_name], 0 ) == -1 )
        play_error(FX_FILENAMES[fx_name]);
}

void Sound_playBGM() {
    if (Mix_PlayingMusic() == 0) Mix_PlayMusic( BGM, -1 );
}

void Sound_stopBGM() {
    Mix_HaltMusic();
}

void Sound_close() {
    int i;

    /* Libera efeitos sonoros */
    for (i = 0; i < FX_TOTAL; ++i) {
        Mix_FreeChunk(FX[i]);
    }

    /* Libera música */
    Mix_FreeMusic(BGM);
}
