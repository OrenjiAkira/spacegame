#ifndef GAME_PATH_H
#define GAME_PATH_H

typedef struct _path Path;
/* Path
 */

void Path_init(char *execpath);
/*
 */

char* Path_toExecutable();
/*
 */

char* Path_toSprites();
/*
 */

char* Path_toFonts();
/*
 */


#endif
