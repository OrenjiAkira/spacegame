
#include "debug.h"
#include "config/path.h"

#include <stdio.h>
#include <string.h>

struct _path {
    char executable[128];
    char sprites[128];
    char fonts[128];
};

static Path PATH;

void Path_init(char const *execpath) {
    int i = strlen(execpath);

    strcpy(PATH.executable, execpath);

    while (i-- > 0) if (PATH.executable[i] == '/') break;

    PATH.executable[i+1] = '\0';

    strcpy(PATH.sprites, PATH.executable);
    strcat(PATH.sprites, "assets/sprites/");
    logprint("SPRITE FOLDER PATH: %s\n", PATH.sprites);

    strcpy(PATH.fonts, PATH.executable);
    strcat(PATH.fonts, "assets/fonts/");
    logprint("FONT FOLDER PATH: %s\n", PATH.fonts);
}

char* Path_toExecutable() {
    return PATH.executable;
}

char* Path_toSprites() {
    return PATH.sprites;
}

char* Path_toFonts() {
    return PATH.fonts;
}
