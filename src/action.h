#ifndef GAME_ACTION_H
#define GAME_ACTION_H

enum _action_pools {
    ACTION_MOVEFWD,
    ACTION_TURNRGT,
    ACTION_TURNLFT,
    ACTION_AUTODIE,
    ACTION_GRAVITY,
    ACTION_COLLIDE,
    ACTION_ANIMATE,
    ACTION_LIST_SIZE
};

void Action_init();
/* () -> void
 */

void Action_add(int POOL, int id);
/* () -> void
 */

void Action_remove(int POOL, int id);
/* () -> void
 */

void Action_update();
/* () -> void
 */

#endif
