
#include "game.h"
#include "window.h"
#include "action.h"
#include "sound.h"
#include "input.h"
#include "config/path.h"
#include "config/conf.h"
#include "config/map.h"
#include "config/font.h"
#include "config/time.h"
#include "utility/vector.h"
#include "utility/direction.h"
#include "components/physics.h"
#include "components/drawpos.h"
#include "components/drawquad.h"
#include "components/sprite.h"
#include "components/textbox.h"
#include "components/timer.h"
#include "scenes/pressstart.h"

#include <stdio.h>
#include <stdbool.h>

static long unsigned int framecount = 0;
static bool QUIT = false;

static void Game_load() {
    PressStart_load();
    logprint("UNITS: \n [ %f, %f ]\n", Map_getUnitX(), Map_getUnitY());
}

void Game_init(char const *execpath) {

    logprint("Initializing:\n");


    /* Window */
    logprint(" > Window\n");
    Window_init();
    logprint(" > Input\n");
    Input_init();

    /* Configuration */
    logprint(" > Conf Path\n");
    Path_init(execpath);

    logprint(" > Conf Strings\n");
    Conf_init();

    logprint(" > Conf Time\n");
    Time_init();

    logprint(" > Conf Map\n");
    Map_init();

    logprint(" > Conf Font\n");
    Font_init();

    /* Utilities */
    logprint(" > Direction\n");
    Direction_init();

    /* Components */
    logprint(" > Timers\n");
    Timer_init();
    logprint(" > Physics\n");
    Physics_init();
    logprint(" > DrawPos\n");
    DrawPos_init();
    logprint(" > DrawQuad\n");
    DrawQuad_init();
    logprint(" > Sprite\n");
    Sprite_init();
    logprint(" > Textbox\n");
    Textbox_init();

    /* Entities */
    logprint(" > Entity\n");
    Entity_init();

    /* Actions */
    logprint(" > Action\n");
    Action_init();

    /* Sound */
    logprint(" > Sound\n");
    Sound_init();

    /* Load game */
    logprint("Loading game...\n");
    Game_load();
}

bool Game_update() {
    /* Qualquer uma dessas funções podem chamar
    a função Game_quit() e mudar o valor de QUIT. */
    Input_update();
    Action_update();
    Timer_update();
    Physics_update();
    DrawPos_update();
    Sprite_update();
    Textbox_update();
    Window_update();

    /* logprint("[Running at %d FPS]\n", Time_getFramerate());
    logprint("Framecount: %lu\n\n", ++framecount); */
    ++framecount;

    return QUIT;
}

void Game_quit() {
    logprint("\t> Game quit called.\n");
    QUIT = true;
}

void Game_close() {
    logprint("Framecount: %lu (%f secs)\n\n", framecount, framecount*1.0/Time_getFramerate());

    Entity_close();

    DrawQuad_close();
    Sprite_close();
    Textbox_close();

    Font_close();

    Sound_close();

    Window_close();
}
