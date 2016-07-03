
#include "debug.h"
#include "game.h"
#include "config/glob.h"

static int GLOBALS[GLOBAL_TOTAL];

void Globals_init() {
    /* Pedante */
    int i; for (i = 0; i < GLOBAL_TOTAL; ++i) GLOBALS[i] = 0;
}

int Globals_get(int global_id) {
    logprint("Requested global id #%d", global_id);
    if (global_id < 0 || global_id >= GLOBAL_TOTAL) {
        GAME_ERROR("INVALID GLOBAL ID REQUESTED. Preventing segmentation fault, but shutting down game.");
        return 0;
    }
    return GLOBALS[global_id];
}

void Globals_set(int global_id, int value) {
    logprint("Requested global id #%d", global_id);
    if (global_id < 0 || global_id >= GLOBAL_TOTAL) {
        GAME_ERROR("INVALID GLOBAL ID REQUESTED. Preventing segmentation fault, but shutting down game.");
        return;
    }
    GLOBALS[global_id] = value;
}
