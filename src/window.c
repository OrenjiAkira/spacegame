
#include "game.h"
#include "window.h"
#include "config/time.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

struct _window {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

static Window WINDOW;

void Window_init() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {   
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        Game_quit();
    }

    if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        Game_quit();
    }

    if( TTF_Init() == -1 ) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        Game_quit();
    }

    WINDOW.window = SDL_CreateWindow( "Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    if (WINDOW.window == NULL) {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        Game_quit();
    }

    WINDOW.renderer = SDL_CreateRenderer(WINDOW.window, -1, SDL_RENDERER_ACCELERATED);
    if (WINDOW.renderer == NULL) {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        Game_quit();
    }

    SDL_SetRenderDrawColor( WINDOW.renderer, 0xFF, 0x00, 0xFF, 0xFF );
    printf("SDL and its components initialized. Window initialized.\n");
}

SDL_Renderer* Window_getRenderer() {
    return WINDOW.renderer;
}

void Window_update() {
    SDL_RenderPresent( WINDOW.renderer );
    SDL_Delay( Time_getFramemilisec() );
}

void Window_close() {
    SDL_DestroyRenderer(WINDOW.renderer);
    SDL_DestroyWindow(WINDOW.window);
    
    WINDOW.renderer = NULL;
    WINDOW.window = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
