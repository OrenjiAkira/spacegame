
#include "game.h"
#include "factory.h"
#include "window.h"
#include "action.h"
#include "input.h"
#include "config/path.h"
#include "config/conf.h"
#include "config/map.h"
#include "config/font.h"
#include "config/time.h"
#include "utility/macros.h"
#include "utility/vector.h"
#include "utility/direction.h"
#include "components/physics.h"
#include "components/drawpos.h"
#include "components/drawquad.h"
#include "components/sprite.h"
#include "components/textbox.h"
#include "components/timer.h"
#include "controllers/space.h"

#include <stdio.h>
#include <stdbool.h>

static long unsigned int framecount = 0;
static bool QUIT = false;

static int PLAYER1, PLAYER2;

static void Game_load() {
    Factory_loadBackground();
    Factory_loadPlanet();
    Factory_loadPlayer1();
    Factory_loadPlayer2();

    SpaceController_load();

    printf("UNITS: \n [ %f, %f ]\n", Map_getUnitX(), Map_getUnitY());
}

void Game_setPlayer1(int id) {
    PLAYER1 = id;
}

void Game_setPlayer2(int id) {
    PLAYER2 = id;
}

int Game_getPlayer1() {
    return PLAYER1;
}

int Game_getPlayer2() {
    return PLAYER2;
}

void Game_init(char *execpath) {
    /* Configuration */
    Path_init(execpath);
    Conf_init();
    Time_init();
    Map_init();
    Font_init();

    /* Window */
    Window_init();
    Input_init();

    /* Utilities */
    Direction_init();

    /* Components */
    Timer_init();
    Physics_init();
    DrawPos_init();
    DrawQuad_init();
    Sprite_init();
    Textbox_init();

    /* Entities */
    Entity_init();

    /* Actions */
    Action_init();

    /* Load game */
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

    printf("[Running at %d FPS]\n", Time_getFramerate());
    printf("Framecount: %lu\n\n", ++framecount);

    return QUIT;
}

void Game_quit() {
    QUIT = true;
}

void Game_close() {
    Entity_close();

    DrawQuad_close();
    Sprite_close();
    Textbox_close();
    
    Font_close();

    Window_close();
}

