
#include "config/path.h"
#include "config/font.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>

struct _font {
    SDL_Color color[FONTSIZE_TOTAL];
    TTF_Font *font[FONTCOLOR_TOTAL];
};

static Font FONTCONF;

void Font_init() {
    char fontpath[128];

    FONTCONF.color[FONTCOLOR_WHITE].r = 255;
    FONTCONF.color[FONTCOLOR_WHITE].g = 255;
    FONTCONF.color[FONTCOLOR_WHITE].b = 255;

    FONTCONF.color[FONTCOLOR_GREY].r = 100;
    FONTCONF.color[FONTCOLOR_GREY].g = 100;
    FONTCONF.color[FONTCOLOR_GREY].b = 100;

    FONTCONF.color[FONTCOLOR_GREEN].r = 40;
    FONTCONF.color[FONTCOLOR_GREEN].g = 255;
    FONTCONF.color[FONTCOLOR_GREEN].b = 80;

    FONTCONF.color[FONTCOLOR_RED].r = 255;
    FONTCONF.color[FONTCOLOR_RED].g = 80;
    FONTCONF.color[FONTCOLOR_RED].b = 80;

    fontpath[0] = '\0';
    strcat(fontpath, Path_toFonts());
    strcat(fontpath, "/PressStart2P.ttf");
    FONTCONF.font[0] = TTF_OpenFont(fontpath, 8);
    FONTCONF.font[1] = TTF_OpenFont(fontpath, 14);
    FONTCONF.font[2] = TTF_OpenFont(fontpath, 21);
    FONTCONF.font[3] = TTF_OpenFont(fontpath, 28);
}

TTF_Font* Font_getFont(int size) {
    return FONTCONF.font[size];
}

SDL_Color Font_getColor(int color) {
    return FONTCONF.color[color];
}

void Font_close() {
    int i;
    for (i = 0; i < FONTSIZE_TOTAL; ++i) {
        TTF_CloseFont(FONTCONF.font[i]);
        FONTCONF.font[i] = NULL;
    }
}
