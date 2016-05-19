
#include "game.h"
#include "config/conf.h"
#include "utility/macros.h"
#include "utility/vector.h"
#include "components/physics.h"
#include "components/drawpos.h"
#include "components/drawquad.h"
#include "components/sprite.h"
#include "entities/planet.h"
#include "entities/picture.h"

#include <stdio.h>

void Game_init() {
    int phys, dquad, dpos, sprite;
    int planet, bg;
    float m, r, x, y;

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

}
