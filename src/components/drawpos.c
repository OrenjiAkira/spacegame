
#include "utility/macros.h"
#include "components/physics.h"
#include "components/drawpos.h"

#include <stdbool.h>
#include <stdio.h>

struct _drawpos {
    SDL_Rect pos;
    int phys_id;
    bool active;
};

static DrawPos DRAWPOS[DRAWPOS_POOL_SIZE];

static void DrawPos_align(int id) {
    Vector *position = Physics_getPos(DRAWPOS[id].phys_id);

    DRAWPOS[id].pos.x = UNIT_X * position->x / MAP_WIDTH;
    DRAWPOS[id].pos.y = UNIT_Y * position->y / MAP_HEIGHT;
}

void DrawPos_init() {
    int id;

    for (id = 0; id < DRAWPOS_POOL_SIZE; ++id)
        DRAWPOS[id].active = false;
}

int DrawPos_new(int body_id, int qw, int qh) {
    int id;

    for (id = 0; id < DRAWPOS_POOL_SIZE; ++id)
        if (!DRAWPOS[id].active) {
            DRAWPOS[id].phys_id = body_id;
            DRAWPOS[id].active = true;
            DRAWPOS[id].pos.w = qw;
            DRAWPOS[id].pos.h = qh;
            DrawPos_align(id);
            return id;
        }
}

void DrawPos_kill(int id) {

}

void DrawPos_update() {
    int id;

    for (id = 0; id < DRAWPOS_POOL_SIZE; ++id)
        if (DRAWPOS[id].active)
            DrawPos_align(id);
}

SDL_Rect* DrawPos_getPos(int id) {
    return (DRAWPOS[id].active ? DRAWPOS[id].pos : NULL);
}

