
#include "utiility/macros.h"
#include "utiility/thing.h"

#include <stdbool.h>
#include <stdio.h>

struct _thing {
    int framerate;
    double frameunit;
};

static Thing THING;

void Thing_init() {
    /* Init framerate and frameunit */
}

int Thing_getFramerate() {
    return THING.framerate;
}

int Thing_getFrameunit() {
    return THING.frameunit;
}
