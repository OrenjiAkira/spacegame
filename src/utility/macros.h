#ifndef GAME_MACROS
#define GAME_MACROS

#include "game.h"

#define GAME_ERROR(error) printf("ERROR: " #error "\n"); Game_quit()

#define pool_overflow(type) GAME_ERROR(#type " pool overflow"); return 0

#endif
