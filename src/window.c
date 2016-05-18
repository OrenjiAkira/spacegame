
#include "window.h"
#include "config/time.h"

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

struct _window {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

static SDL_Event EVENTS;
static Window WINDOW;

void Window_init() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );

    WINDOW.window = SDL_CreateWindow( "Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    WINDOW.renderer = SDL_CreateRenderer(WINDOW.window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor( WINDOW.renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

SDL_Renderer* Window_getRenderer() {
    return WINDOW.renderer;
}

bool Window_update() {
    bool quit = false;
    while( SDL_PollEvent( &EVENTS ) != 0 )
        if( EVENTS.type == SDL_QUIT )
            quit = true;
    SDL_Delay( Time_getFramemilisec() );
    return quit;
}

void Window_close() {
    SDL_DestroyRenderer(WINDOW.renderer);
    SDL_DestroyWindow(WINDOW.window);
    
    WINDOW.renderer = NULL;
    WINDOW.window = NULL;

    SDL_Quit();
}
