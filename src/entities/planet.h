#ifndef GAME_PLANET_H
#define GAME_PLANET_H

#define PLANET_POOL_SIZE 4

void Planet_init();

int Planet_new(int physics, int drawquad, int drawpos, int sprite);

void Planet_update();

void Planet_destroy(int id);

void Planet_close();

#endif
