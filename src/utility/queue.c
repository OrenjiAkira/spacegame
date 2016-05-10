
#include "utility/message.h"
#include "utility/queue.h"

struct _queue {
    Message messages[1024];
    int head;
    int tail;
}

void Queue_init(Queue *queue) {
    queue->head = queue->tail = 0;
}

void Queue_push(Queue *queue, char m, Entity *e, void *p) {
    Message_set(&queue->messages[tail], m, e, p);
    queue->tail = (queue->tail + 1) % QUEUE_SIZE;
}

Message Queue_pop(Queue *queue) {
    Message message = queue->messages[queue->head];
    queue->head = (queue->head + 1) % QUEUE_SIZE;
    return message;
}
