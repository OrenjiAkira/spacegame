
#include "config/path.h"
#include "config/conf.h"

#include <stdio.h>
#include <string.h>

static char CONFIG[CONF_LENGTH][BUFFER_SIZE];

void Conf_init() {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char section[32];
    int n;

    buffer[0] = '\0';
    strcat(buffer, Path_toExecutable());
    strcat(buffer, "data\0");

    fp = fopen(buffer, "r");

    do {
        /* buffer = whole new line */
        fgets(buffer, BUFFER_SIZE, fp);

        /* section = first word of the line */
        sscanf(buffer, "%s%n", section, &n);

        /* What to do about it */
        if (!strcmp(section, "framerate"))
            strcpy(CONFIG[CONF_FRAMERATE], buffer+n);
        else if (!strcmp(section, "map"))
            strcpy(CONFIG[CONF_MAP], buffer+n);
        else if (!strcmp(section, "planet"))
            strcpy(CONFIG[CONF_PLANET], buffer+n);
        else if (!strcmp(section, "ship1"))
            strcpy(CONFIG[CONF_SHIP1], buffer+n);
        else if (!strcmp(section, "ship2"))
            strcpy(CONFIG[CONF_SHIP2], buffer+n);
        else if (!strcmp(section, "bullet"))
            strcpy(CONFIG[CONF_BULLETS], buffer+n);
    } while (strcmp(section, "EOF"));

    fclose(fp);
}

char* Conf_get(int section_name) {
    return CONFIG[section_name];
}
