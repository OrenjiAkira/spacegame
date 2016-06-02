#ifndef SYMBOL
#define SYMBOL value

#include <SDL.h>
#include <SDL_ttf.h>

typedef struct _font Font;
/* Font
Struct de fonte. Armazena os diferentes tamanhos e cores
de fonte utilizados pelo jogo. */

enum _fontsize {
    FONTSIZE_SMALL,
    FONTSIZE_MEDIUM,
    FONTSIZE_BIG,
    FONTSIZE_BIGGEST,
    FONTSIZE_TOTAL
};

enum _fontcolor {
    FONTCOLOR_WHITE,
    FONTCOLOR_GREY,
    FONTCOLOR_RED,
    FONTCOLOR_GREEN,
    FONTCOLOR_TOTAL
};

void Font_init();
/* () -> void
Inicializa os diferentes tamanhos e cores de fonte utilizados no jogo. */

TTF_Font* Font_getFont(int size);
/* (int) -> TTF_Font*
Retorna a fonte do tamanho especificado. */

SDL_Color Font_getColor(int color);
/* (int) -> SDL_Color
Retorna a cor de fonte especificada. */

void Font_close();
/* () -> void
Libera a memória ocupada pelos tamanhos de fonte carregados. */


#endif
