
#include "config/map.h"
#include "utility/macros.h"
#include "utility/vector.h"
#include "components/physics.h"
#include "components/drawpos.h"

#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>

struct _drawpos {
    SDL_Rect pos;
    Vector offset;
    int phys_id;
    bool active;
};

static DrawPos DRAWPOS[DRAWPOS_POOL_SIZE];

static void DrawPos_align(int id) {
    Vector *position = Physics_getPos(DRAWPOS[id].phys_id);

    DRAWPOS[id].pos.x = Map_getUnitX() * position->x - DRAWPOS[id].offset.x;
    DRAWPOS[id].pos.y = Map_getUnitY() * position->y - DRAWPOS[id].offset.y;
}

void DrawPos_init() {
    int id;

    for (id = 0; id < DRAWPOS_POOL_SIZE; ++id)
        DRAWPOS[id].active = false;
}

int DrawPos_new(int body_id, int qw, int qh, float ox, float oy) {
    int id;

    for (id = 0; id < DRAWPOS_POOL_SIZE; ++id) {
        if (!DRAWPOS[id].active) {
            DRAWPOS[id].phys_id = body_id;
            DRAWPOS[id].active = true;
            DRAWPOS[id].pos.w = qw;
            DRAWPOS[id].pos.h = qh;
            Vector_set(&DRAWPOS[id].offset, ox, oy);
            DrawPos_align(id);
            return id;
        }
    }
    pool_overflow(DrawPos);
}

void DrawPos_kill(int id) {
    if (!DRAWPOS[id].active) return;
    DRAWPOS[id].active = false;
}

void DrawPos_update() {
    int id;

    for (id = 0; id < DRAWPOS_POOL_SIZE; ++id)
        if (DRAWPOS[id].active)
            DrawPos_align(id);
}

SDL_Rect* DrawPos_getPos(int id) {
    return (DRAWPOS[id].active ? &DRAWPOS[id].pos : NULL);
}

