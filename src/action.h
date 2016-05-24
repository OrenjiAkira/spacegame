#ifndef GAME_ACTION_H
#define GAME_ACTION_H

/* Assumindo a existência de um ponteiro tipo (Entity*) chamado "entity" */
#define GET_ENTITY(pool_name) \
    if ( (entity = Entity_get(POOL[i])) == NULL ) { Action_remove(pool_name, POOL[i]); continue; }

#define FOREACH_VALID_ENTITY(pool_pointer) \
    int i; for (i = 0; i < ENTITY_POOL_SIZE; ++i) if (pool_pointer[i] != -1)

enum _action_pools {
    ACTION_MOVEFWD,
    ACTION_TURNRGT,
    ACTION_TURNLFT,
    ACTION_AUTODIE,
    ACTION_GRAVITY,
    ACTION_COLLIDE,
    ACTION_SHOOTIT,
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
