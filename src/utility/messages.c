
#include "utility/messages.h"

void Message_set(Message *message, char m, Entity *e, void *p) {
    message->m = m;
    message->e = e;
    message->p = p;
}

