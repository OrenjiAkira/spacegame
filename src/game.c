
#include "game.h"
#include "config/conf.h"
#include "utility/macros.h"
#include "utility/vector.h"
#include "components/physics.h"
#include "components/drawpos.h"
#include "components/drawquad.h"
#include "components/sprite.h"
#include "entities/planet.h"

#include <stdio.h>

void Game_init() {
    char* planet_str = Conf_get(CONF_PLANET);
    int phys, dquad, dpos, sprite, planet;
    float m, r, x, y;

    sscanf(planet_str, "%f %f %f %f", &m, &r, &x, &y);
    phys = Physics_new(m, r, x, y, 0, 0);
    dquad = DrawQuad_new(512, 128, 128, 128);
    dpos = DrawPos_new(phys, 128, 128, 64, 64);
    sprite = Sprite_new("planet.png", dpos, dquad);
    planet = Planet_new(phys, dquad, dpos, sprite);
}
