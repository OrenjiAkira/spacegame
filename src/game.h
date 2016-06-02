#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define GAME_ERROR(error) printf("ERROR: " #error "\n"); Game_quit()
#define POOL_OVERFLOW(type) GAME_ERROR(#type " pool overflow"); return 0

void Game_init(char *execpath);
/* () -> void
 */

void Game_setPlayer1(int id);
/* (int) -> void
 */

void Game_setPlayer2(int id);
/* (int) -> void
 */

int Game_getPlayer1();
/* () -> int
 */

int Game_getPlayer2();
/* () -> int
 */

bool Game_update();
/* () -> void
 */

void Game_quit();
/* () -> void
 */

void Game_close();
/* () -> void
 */

#endif
