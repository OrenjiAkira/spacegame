
#include "game.h"
#include "window.h"
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
#include "entities/planet.h"
#include "entities/ship.h"
#include "entities/picture.h"
#include "controllers/space.h"

#include <stdio.h>
#include <stdbool.h>

static long unsigned int framecount = 0;
static bool QUIT = false;

static int PLAYER1, PLAYER2;

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
    Picture_init();
    Planet_init();
    Ship_init();

    /* Load game */
    Game_load();
}

void Game_load() {
    float m, r, x, y, vx, vy;
    int phys, dquad, dpos, sprite, textbox;
    int planet, bg;
    char name[128];
    

    /* Planet */
    Conf_getPlanetValues(&m, &r, &x, &y);
    phys = Physics_new(m, r, x, y, 0, 0);
    dquad = DrawQuad_new(1408, 128, 128, 128);
    dpos = DrawPos_new(phys, 128, 128, 64, 64);
    sprite = Sprite_new("planetv2.png", dpos, dquad, 1);
    planet = Planet_new(phys, dquad, dpos, sprite);
    printf("planet id: %d\n", planet);

    /* Background */
    dpos = DrawPos_new(-1, 800, 600, 400, 300);
    sprite = Sprite_new("background.png", dpos, -1, 0);
    bg = Picture_new(dpos, sprite);
    printf("picture id: %d\n", bg);

    /* Ships */
    printf("%s\n", Conf_getString(CONF_SHIP1));
    Conf_getShipValues(0, name, &m, &r, &x, &y, &vx, &vy);
    phys = Physics_new(m, r, x, y, vx, vy);
    dquad = DrawQuad_new(768, 64, 64, 64);
    dpos = DrawPos_new(phys, 64, 64, 32, 32);
    sprite = Sprite_new("cat00.png", dpos, dquad, 1);
    dpos = DrawPos_new(phys, 0, 0, 0, 0);
    textbox = Textbox_new(name, dpos, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    PLAYER1 = Ship_new(phys, dquad, dpos, sprite, textbox);
    printf("ship id: %d\n", PLAYER1);

    printf("%s\n", Conf_getString(CONF_SHIP2));
    Conf_getShipValues(1, name, &m, &r, &x, &y, &vx, &vy);
    phys = Physics_new(m, r, x, y, vx, vy);
    dquad = DrawQuad_new(768, 64, 64, 64);
    dpos = DrawPos_new(phys, 64, 64, 32, 32);
    sprite = Sprite_new("cat01.png", dpos, dquad, 1);
    dpos = DrawPos_new(phys, 0, 0, 0, 0);
    textbox = Textbox_new(name, dpos, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    PLAYER2 = Ship_new(phys, dquad, dpos, sprite, textbox);
    printf("ship id: %d\n", PLAYER2);

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

bool Game_update() {
    /* Qualquer uma dessas funções podem chamar
    a função Game_quit() e mudar o valor de QUIT. */

    Input_update();

    Picture_update();
    Planet_update();
    Ship_update();

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
    Ship_close();
    Planet_close();
    Picture_close();

    DrawQuad_close();
    Sprite_close();
    Textbox_close();
    
    Font_close();

    Window_close();
}

