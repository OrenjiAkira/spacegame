#ifndef GAME_PICTURE_H
#define GAME_PICTURE_H

#define PICTURE_POOL_SIZE 16

void Picture_init();

int Picture_new(int drawpos, int sprite);

void Picture_update();

void Picture_destroy(int id);

void Picture_close();


#endif
