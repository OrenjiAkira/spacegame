
#include "game.h"
#include "window.h"
#include "config/path.h"
#include "config/conf.h"
#include "config/time.h"
#include "config/map.h"
#include "utility/vector.h"
#include "utility/direction.h"
#include "components/timer.h"
#include "components/physics.h"
#include "components/drawpos.h"
#include "components/drawquad.h"
#include "components/sprite.h"
#include "entities/planet.h"

#include <stdio.h>
#include <stdbool.h>

static bool load(char* execpath) {
    bool quit = false;

    /* Configuration */
    Path_init(execpath);
    Conf_init();
    Time_init();
    Map_init();

    /* Window */
    Window_init();

    /* Utilities */
    Direction_init();

    /* Components */
    Timer_init();
    Physics_init();
    DrawPos_init();
    DrawQuad_init();
    Sprite_init();

    /* Entities */
    Planet_init();

    Game_init();

    return quit;
}

static bool update() {
    bool quit = false;

    Planet_update();

    Timer_update();
    Physics_update();
    DrawPos_update();
    Sprite_update();

    quit = Window_update();

    return quit;
}

static void close() {

    Planet_close();

    DrawQuad_close();
    Sprite_close();
    Window_close();
}

int main(int argc, char *argv[]) {
    long unsigned int framecount = 0;
    bool quit;
    
    quit = load( argv[0] );

    while (!quit) {
        printf("[Running at %d FPS]\n", Time_getFramerate());
        printf("Framecount: %lu\n\n", framecount++);
        quit = update();
    }

    close();

    return 0;
}
