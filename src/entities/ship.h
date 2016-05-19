#ifndef GAME_SHIP_H
#define GAME_SHIP_H

#define SHIP_POOL_SIZE 2

void Ship_init();

int Ship_new(int physics, int drawquad, int drawpos, int sprite, int textbox);

void Ship_update();

void Ship_destroy(int id);

void Ship_close();

void Ship_accelerate(int id);

void Ship_turnLeft(int id);

void Ship_turnRight(int id);

#endif
