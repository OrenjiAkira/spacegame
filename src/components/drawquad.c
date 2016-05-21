
#include "utility/macros.h"
#include "components/drawquad.h"

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

struct _drawquad {
    SDL_Rect *quads;
    int current;
    int count;
    bool active;
};

static DrawQuad DRAWQUADS[DRAWQUAD_POOL_SIZE];

void DrawQuad_init() {
    int id;
    for (id = 0; id < DRAWQUAD_POOL_SIZE; ++id) {   
        DRAWQUADS[id].active = false;
        DRAWQUADS[id].quads = NULL;
    }
}

int DrawQuad_new(int w, int h, int qw, int qh) {
    int id, rows, cols, i, j;
    for (id = 0; id < DRAWQUAD_POOL_SIZE; ++id) {
        if (!DRAWQUADS[id].active) {
            rows = h / qh;
            cols = w / qw;
            DRAWQUADS[id].current = 0;
            DRAWQUADS[id].count = cols * rows;
            DRAWQUADS[id].active = true;

            /* Colocamos todos os quads num vetor linear */
            DRAWQUADS[id].quads = (SDL_Rect*)malloc( DRAWQUADS[id].count * sizeof(SDL_Rect) );
            for (i = 0; i < cols; ++i) {
                for (j = 0; j < rows; ++j) {
                    DRAWQUADS[id].quads[i*rows + j].x = i*qw;
                    DRAWQUADS[id].quads[i*rows + j].y = j*qh;
                    DRAWQUADS[id].quads[i*rows + j].w = qw;
                    DRAWQUADS[id].quads[i*rows + j].h = qh;
                }
            }
            return id;
        }
    }
    pool_overflow(DrawQuad);
}

void DrawQuad_kill(int id) {
    if (id == -1 || !DRAWQUADS[id].active) return;
    free(DRAWQUADS[id].quads);
    DRAWQUADS[id].quads = NULL;
    DRAWQUADS[id].active = false;
}

void DrawQuad_next(int id) {
    if (id == -1 || !DRAWQUADS[id].active) return;
    DRAWQUADS[id].current = (DRAWQUADS[id].current + 1) % DRAWQUADS[id].count;
}

void DrawQuad_prev(int id) {
    if (id == -1 || !DRAWQUADS[id].active) return;
    DRAWQUADS[id].current = (DRAWQUADS[id].current + DRAWQUADS[id].count - 1) % DRAWQUADS[id].count;
}

void DrawQuad_change(int id, int quad) {
    if (id == -1 || !DRAWQUADS[id].active) return;
    DRAWQUADS[id].current = quad % DRAWQUADS[id].count;
}

SDL_Rect* DrawQuad_getQuad(int id) {
    if (id == -1 || !DRAWQUADS[id].active) return NULL;
    return &DRAWQUADS[id].quads[DRAWQUADS[id].current];
}

void DrawQuad_close() {
    int id;
    for (id = 0; id < DRAWQUAD_POOL_SIZE; ++id)
        DrawQuad_kill(id);
}
