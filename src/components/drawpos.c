
#include "game.h"
#include "window.h"
#include "config/map.h"
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

static void DrawPos_alignWithoutPhysics(int id, Vector* position) {
    DRAWPOS[id].pos.x = Map_getUnitX() * (position->x + Map_getWidth()/2) - DRAWPOS[id].offset.x;
    DRAWPOS[id].pos.y = Map_getUnitY() * (position->y + Map_getHeight()/2) - DRAWPOS[id].offset.y;
}

static void DrawPos_align(int id) {
    Vector *position;

    if (DRAWPOS[id].phys_id != -1) {
        position = Physics_getPos(DRAWPOS[id].phys_id);
        DrawPos_alignWithoutPhysics(id, position);
    }

}

void DrawPos_init() {
    int id;

    for (id = 0; id < DRAWPOS_POOL_SIZE; ++id) {
        DRAWPOS[id].active = false;
    }
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
    POOL_OVERFLOW(DrawPos);
}

void DrawPos_kill(int id) {
    if (id == -1 || !DRAWPOS[id].active) return;
    DRAWPOS[id].active = false;
}

void DrawPos_update() {
    int id;

    for (id = 0; id < DRAWPOS_POOL_SIZE; ++id)
        if (DRAWPOS[id].active)
            DrawPos_align(id);
}

SDL_Rect* DrawPos_getPos(int id) {
    if (id == -1 || !DRAWPOS[id].active) return NULL;
    return &DRAWPOS[id].pos;
}

void DrawPos_setPos(int id, Vector *pos) {
    if (id == -1 || !DRAWPOS[id].active) return;
    DrawPos_alignWithoutPhysics(id, pos);
}

Vector* DrawPos_getOffset(int id) {
    if (id == -1 || !DRAWPOS[id].active) return NULL;
    return &DRAWPOS[id].offset;
}

void DrawPos_print(int id) {
    if (id == -1 || !DRAWPOS[id].active) return;
    logprint(">> DRAWPOS INFO: #%d\n", id);
    logprint(">>       RECT [ x: %d, y: %d, w: %d, h: %d ]\n", DRAWPOS[id].pos.x, DRAWPOS[id].pos.y, DRAWPOS[id].pos.w, DRAWPOS[id].pos.h);
    logprint(">>     OFFSET [ ox: %f, oy: %f ]\n", DRAWPOS[id].offset.x, DRAWPOS[id].offset.y);
}
