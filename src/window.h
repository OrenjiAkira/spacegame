#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct _window Window;

void Window_init();
/* () -> void
 */

SDL_Renderer* Window_getRenderer();
/* () -> SDL_Surface*
 */

bool Window_update();
/* () -> void
 */

void Window_close();
/* () -> void
 */

#endif
