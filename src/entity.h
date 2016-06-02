#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <stdbool.h>

#define ENTITY_POOL_SIZE 128

#define VERIFY_ENTITY(id) if (ENTITIES[id] == NULL) { printf("INVALID ENTITY ID #%d. ENTITY IS NOT ACTIVE.\n", id); return; }

enum _timer_types {
    TIMER_INPUTDELAY1,
    TIMER_INPUTDELAY2,
    TIMER_COUNTDOWN1,
    TIMER_COUNTDOWN2,
    TIMER_ANIMATION,
    TIMER_TYPES_TOTAL
};
/* Cada elemento possui uma lista de timers separados
cada um para uma função específica. Dessa forma evitamos
conflitos entre timers. */

typedef struct _entity {
    int physics;
    int drawpos;
    int drawquad;
    int sprite;
    int textbox;
    int timers[TIMER_TYPES_TOTAL];
} Entity;
/* Entity
Uma struct básica que pode armazenar vários componentes.
Componentes inativos são representados pelo valor -1. */

void Entity_init();
/* () -> void
Inicializa a pool de entidades. */

int Entity_new(int physics, int drawquad, int drawpos, int sprite, int textbox);
/* (int, int, int ,int ,int) -> int
Recebe cinco IDs, cada um de um tipo de componente.
O ID pode ser -1 para indicar que a entidade não
usa aquele componente. Retorna um valor inteiro que
representa o índice da entidade na pool. */

Entity* Entity_get(int id);
/* (int) -> Entity*
Recebe um ID de entidade, e retorna o seu ponteiro.
Deve-se ao máximo evitar de usar essa função. Ela
existe APENAS para as AÇÕES terem acesso aos
componentes de uma entidade. Idealmente nenhuma
outra parte do código deve chamar essa função.
Não há nenhum problema em utilizá-la, mas é boa
prática não acessar diretamente a um item de uma
pool. Mas como as entidades não fazem nada (porque
elas não sabem seus tipos), ALGUÉM precisa saber
e acessar seus componentes.

Na real, eu devia ter feito métodos getter para cada
componente, mas estava com preguiça mesmo. E isso
facilita a uniformidade do código das ações e
as suas verificações respectivas. */

void Entity_addTimer(int id, int timer_type, double secs);
/* (int, int, double) -> void
Recebe um ID de uma entidade, um tipo de timer,
e um tempo em segundos. Cria um timer do tipo
especificado com o tempo especificado. */

bool Entity_isTimerDone(int id, int timer_type);
/* (int, int) -> bool
Verifica se o timer <timer_type> de uma entidade terminou.
Retorna true se sim, falso se não. */

void Entity_destroy(int id);
/* (int) -> void
Destrói uma entidade. */

void Entity_close();
/* () -> void
Limpa a pool de entidades e libera
toda a memória alocada pra elas. */

#endif
