
#include "window.h"
#include "config/font.h"
#include "utility/macros.h"
#include "utility/vector.h"
#include "components/drawpos.h"
#include "components/textbox.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct _textbox {
    SDL_Texture *texture;
    int dpos_id;
    bool active;
};

static Textbox TEXTBOX[TEXTBOX_POOL_SIZE];

static void Textbox_align(int id, int align) {
    SDL_Rect *pos = DrawPos_getPos(TEXTBOX[id].dpos_id);
    Vector *offset = DrawPos_getOffset(TEXTBOX[id].dpos_id);
    offset->y = -16;

    if (align == TEXTALIGN_CENTER) {
        offset->x = pos->w/2;
    } else if (align == TEXTALIGN_CENTER) {
        offset->x = pos->w;
    }
}

static void Textbox_loadTexture(int id, char* text, int size, int color) {
    SDL_Surface *textSurface;
    SDL_Rect *pos;

    textSurface = TTF_RenderText_Solid( Font_getFont(size), text, Font_getColor(color) );
    if( textSurface == NULL )
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );

    TEXTBOX[id].texture = SDL_CreateTextureFromSurface( Window_getRenderer(), textSurface );
    if( TEXTBOX[id].texture == NULL )
        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );

    pos = DrawPos_getPos(TEXTBOX[id].dpos_id);
    pos->w = textSurface->w;
    pos->h = textSurface->h;

    SDL_FreeSurface(textSurface);
}

void Textbox_init() {
    int id;
    
    for (id = 0; id < TEXTBOX_POOL_SIZE; ++id) {
        TEXTBOX[id].active = false;
        TEXTBOX[id].texture = NULL;
        TEXTBOX[id].dpos_id = -1;

    }
}

int Textbox_new(char* text, int dpos_id, int align, int size, int color) {
    int id;
    for (id = 0; id < TEXTBOX_POOL_SIZE; ++id) {
        if (!TEXTBOX[id].active) {
            TEXTBOX[id].dpos_id = dpos_id;
            Textbox_loadTexture(id, text, size, color);
            Textbox_align(id, align);
            TEXTBOX[id].active = true;
            return id;
        }
    }
    pool_overflow(Textbox);
}

void Textbox_kill(int id) {
    if (id == -1 || !TEXTBOX[id].active) return;
    SDL_DestroyTexture(TEXTBOX[id].texture);
    TEXTBOX[id].active = false;
    TEXTBOX[id].texture = NULL;
    DrawPos_kill(TEXTBOX[id].dpos_id);
    TEXTBOX[id].dpos_id = -1;
}

void Textbox_update() {
    int id;
    for (id = 0; id < TEXTBOX_POOL_SIZE; ++id)
        if (TEXTBOX[id].active)
            SDL_RenderCopy( Window_getRenderer(), TEXTBOX[id].texture, NULL, DrawPos_getPos(TEXTBOX[id].dpos_id) );
}

void Textbox_close() {
    int id;
    for (id = 0; id < TEXTBOX_POOL_SIZE; ++id) {
        Textbox_kill(id);
    }
}




