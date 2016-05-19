#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct _window Window;

void Window_init();
/* () -> void
 */

SDL_Renderer* Window_getRenderer();
/* () -> SDL_Surface*
 */

void Window_update();
/* () -> void
 */

void Window_close();
/* () -> void
 */

#endif
