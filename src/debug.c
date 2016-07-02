#ifndef DEBUG_MODE

void logprint(char const *fmt, ...) {}

#else

#include <stdio.h>
#include <stdarg.h>

void logprint(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

#endif
