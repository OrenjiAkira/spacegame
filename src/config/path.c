
#include "debug.h"
#include "config/path.h"
#include "utility/string.h"

#include <stdio.h>
#include <string.h>

struct _path {
    char executable[128];
    char sprites[128];
    char se[128];
    char fonts[128];
};

static Path PATH;

void Path_init(char const *execpath) {
    int i = strlen(execpath);

    strcpy(PATH.executable, execpath);

    while (i-- > 0) if (PATH.executable[i] == '/') break;

    PATH.executable[i+1] = '\0';

    String_join(PATH.sprites, PATH.executable, "assets/sprites/");
    logprint("SPRITE FOLDER PATH: %s\n", PATH.sprites);

    String_join(PATH.fonts, PATH.executable, "assets/fonts/");
    logprint("FONT FOLDER PATH: %s\n", PATH.fonts);

    String_join(PATH.se, PATH.executable, "assets/se/");
    logprint("SE FOLDER PATH: %s\n", PATH.se);
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

char* Path_toFX() {
    return PATH.se;
}
