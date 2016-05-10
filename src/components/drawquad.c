
#include "utility/macros.h"

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

struct _drawquad {
    SDL_Rect *quads;
    int current;
    int count;
    bool active;
}

static DrawQuad DRAWQUADS[DRAWQUAD_POOL_SIZE];

static void DrawQuad_readqueue() {
    Message *msg;
    int *q;

    Queue_push(&QUEUE, STOP, NULL, NULL);
    while( (msg = Queue_pop(&QUEUE))->message != STOP) ) {
        switch (msg->message) {
            case UPDT:
                DrawQuad_next(msg->e->drawquad);
                break;
            case CHNG:
                q = (int*)msg->params;
                DrawQuad_change(msg->e->drawquad, *q);
                break;
            case KILL:
                DrawQuad_kill(msg->e->drawquad);
                break;
            default:
                break;
        }
    }
}

void DrawQuad_init() {
    int id;
    for (id = 0; id < DRAWQUAD_POOL_SIZE; ++id)
        DRAWQUADS[id].active = false;
        DRAWQUADS[id].quads = NULL;
}

int DrawQuad_new(int w, int h, int qw, int qh) {
    int id, rows, cols, i, j;
    for (id = 0; id < DRAWQUAD_POOL_SIZE; ++id) {
        rows = h / qh;
        cols = w / qw;
        DRAWQUADS[id].current = 0;
        DRAWQUADS[id].count = cols * rows;
        DRAWQUADS[id].active = true;

        /* Colocamos todos os quads num vetor linear */
        DRAWQUADS[id].quads = (SDL_Rect*)malloc( DRAWQUADS[id].count * sizeof(SDL_Rect) );
        for (i = 0; i < cols; ++i) {
            for (j = 0; j < rows; ++j) {
                DRAWQUADS[id].quads[i*rows + j].x = j*qw;
                DRAWQUADS[id].quads[i*rows + j].y = k*qh;
                DRAWQUADS[id].quads[i*rows + j].w = qw;
                DRAWQUADS[id].quads[i*rows + j].h = qh;
            }
        }
        return id;
    }
    pool_overflow(DrawQuad);
}

void DrawQuad_update() {
    
}






