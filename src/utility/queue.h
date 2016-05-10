#ifndef GAME_QUEUE_H
#define GAME_QUEUE_H

#define QUEUE_SIZE 1024

typedef struct _queue Queue;

void Queue_init(Queue *queue);
/* (Queue*) -> void
 */

void Queue_push(Queue *queue, char *m, Entity *e, void *p);
/* (Queue*, char*, Entity*, void*) -> void
 */

Message Queue_pop(Queue *queue);
/* (Queue*) -> Message
 */

#endif
