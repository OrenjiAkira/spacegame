#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct _window Window;

void Window_init();
/* () -> void
Inicializa janela e renderer. */

SDL_Renderer* Window_getRenderer();
/* () -> SDL_Surface*
Retorna o renderer principal da janela do programa. */

void Window_update();
/* () -> void
Atualiza o renderer principal da janela do programa. */

void Window_close();
/* () -> void
Encerra o renderer e fecha a janela. */

#endif
