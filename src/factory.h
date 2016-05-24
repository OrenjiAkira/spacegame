#ifndef GAME_FACTORY_H
#define GAME_FACTORY_H


/* Load entity from conf */

void Factory_loadPlanet();
/* () -> void
 */

void Factory_loadPlayer1();
/* () -> void
 */

void Factory_loadPlayer2();
/* () -> void
 */

void Factory_loadBackground();
/* () -> void
 */


/* New entity from game */

void Factory_newBullet(int origin_body, float m, float r, float lt);
/* () -> void
 */

void Factory_newExplosion(int origin_body);
/* () -> void
 */


#endif
