
#include "game.h"
#include "config/time.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

static bool init_libs() {
    do {
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
            break;
        }
        if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            break;
        }
        if( TTF_Init() == -1 ) {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            break;
        }
        return false;
    } while (0);

    /* ERROR */
    printf("ERROR: SDL was not initialized. Program shutting down.\n");
    return true;
}

static void close_libs() {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char const *argv[]) {
    bool quit = init_libs();

    /* Inicializa programa. */
    Game_init( argv[0] );

    while (!quit) {
        quit = Game_update();                   /* Main game loop */
        SDL_Delay( Time_getFramemilisec() );    /* FPS delay */
    }

    /* Encerra programa. */
    Game_close();
    close_libs();

    return 0;
}
