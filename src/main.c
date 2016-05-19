
#include "game.h"
#include "config/time.h"

#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    bool quit = false;
    
    Game_init( argv[0] );

    while (!quit) {
        quit = Game_update();
    }

    Game_close();

    return 0;
}
