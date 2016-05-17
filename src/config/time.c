
#include "utility/macros.h"
#include "config/conf.h"
#include "config/time.h"

#include <stdio.h>

struct _time {
    int framerate;
    double frameunit;
};

static Time TIMECONF;

void Time_init() {
    char *framerate_str = Conf_get(CONF_FRAMERATE);
    sscanf(framerate_str, "%d", &TIMECONF.framerate);
    TIMECONF.frameunit = 1.0/TIMECONF.framerate;
}

int Time_getFramerate() {
    return TIMECONF.framerate;
}

int Time_getFrameunit() {
    return TIMECONF.frameunit;
}
