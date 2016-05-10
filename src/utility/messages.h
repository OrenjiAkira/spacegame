#ifndef GAME_QUEUE_H
#define GAME_QUEUE_H

#define QUEUE_SIZE 1024

enum _message_dictionary {
    STOP,
    
    PHYSICS_KILL,
    PHYSICS_UPDT,
    PHYSICS_CHNG,
    PHYSICS_MOVE,

    DRAWQUAD_KILL,
    DRAWQUAD_UPDT,
    DRAWQUAD_CHNG,
    
    DRAWPOS_KILL,
    DRAWPOS_UPDT,
    DRAWPOS_CHNG,
    
    SPRITE_KILL,
    SPRITE_UPDT,
    SPRITE_CHNG,
    
    TEXTBOX_KILL,
    TEXTBOX_UPDT,
    TEXTBOX_CHNG,
    
    TIMER_KILL,
    TIMER_UPDT,
    TIMER_CHN_
};

typedef struct _message {
    Entity *entity;
    void *params;
    char message;
} Message;

void Message_set(Message *message, char m, Entity *e, void *p);
/* (Message, char*, Entity*, void*) -> void
 */

#endif
