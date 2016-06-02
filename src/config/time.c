
#include "config/conf.h"
#include "config/time.h"

#include <stdio.h>

struct _time {
    double frameunit;
    int framerate;
    int framems;
};

static Time TIMECONF;

void Time_init() {
    Conf_getFramerateValue(&TIMECONF.framerate);
    TIMECONF.frameunit = 1.0/TIMECONF.framerate;
    TIMECONF.framems = (int)(1000*TIMECONF.frameunit);
}

double Time_getFrameunit() {
    return TIMECONF.frameunit;
}

int Time_getFramerate() {
    return TIMECONF.framerate;
}

int Time_getFramemilisec() {
    return TIMECONF.framems;
}


