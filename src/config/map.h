#ifndef GAME_MAP_H
#define GAME_MAP_H

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct _map Map;

void Map_init();

float Map_getWidth();

float Map_getHeight();

float Map_getUnitX();

float Map_getUnitY();



#endif
