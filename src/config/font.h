#ifndef SYMBOL
#define SYMBOL value

#include <SDL.h>
#include <SDL_ttf.h>

typedef struct _font Font;

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
 */

TTF_Font* Font_getFont(int size);
/* (int) -> TTF_Font*
 */

SDL_Color Font_getColor(int color);
/* (int) -> SDL_Color
 */

void Font_close();
/* () -> void
 */


#endif
