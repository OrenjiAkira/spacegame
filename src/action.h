#ifndef GAME_ACTION_H
#define GAME_ACTION_H

#include "entity.h"

#define ACTION_POOL_SIZE ENTITY_POOL_SIZE

/* Itera por todas as entidades dentro da pool de ação.
Idealmente usa um bloco de código entre chaves logo depois. */
#define FOREACH_VALID_ENTITY(pool_pointer) \
    int i; for (i = 0; i < ENTITY_POOL_SIZE; ++i) if (pool_pointer[i] != -1)

/* Verifica se a entidade na pool existe. Se não existir, remove-a.
Assume a declaração prévia de um ponteiro (Entity* entity). */
#define GET_ENTITY(pool_name) \
    if ( (entity = Entity_get(POOL[i])) == NULL ) { Action_remove(pool_name, POOL[i]); continue; }

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
Inicializa as lista de entidades de cada uma das ações. */

void Action_add(int POOL, int id);
/* (int, int) -> void
Adiciona o ID de uma entidade à lista de uma ação.
Uma entidade estar na lista de uma ação significa
que aquela ação ocorrerá para aquela entidade.
A ação pode ser pontual (resolve-se no mesmo frame
e remove-se da lista) ou contínua (é executada por
um período de frames, esse período podendo ser
definido ou não). */

void Action_remove(int POOL, int id);
/* (int, int) -> void
Remove o ID de uma entidade de lista de uma ação.
Vide função acima. */

void Action_update();
/* () -> void
Itera pelas listas de ações e as executa em ordem. */

#endif
