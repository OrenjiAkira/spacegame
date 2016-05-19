
#include "config/path.h"

#include <stdio.h>
#include <string.h>

struct _path {
    char executable[128];
    char sprites[128];
    char fonts[128];
};

static Path PATH;

void Path_init(char* execpath) {
    int i = strlen(execpath);

    while (i-- > 0)
        if (execpath[i] == '/') break;

    execpath[i+1] = '\0';
    
    strcpy(PATH.executable, execpath);

    strcpy(PATH.sprites, execpath);
    strcat(PATH.sprites, "assets/sprites/");
    printf("SPRITE FOLDER PATH: %s\n", PATH.sprites);
    
    strcpy(PATH.fonts, execpath);
    strcat(PATH.fonts, "assets/fonts/");
    printf("FONT FOLDER PATH: %s\n", PATH.fonts);
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


