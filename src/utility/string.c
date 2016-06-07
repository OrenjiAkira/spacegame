
#include <string.h>

void String_join(char* target, char* const str1, char* const str2) {
    strcpy(target, str1);
    strcat(target, str2);
}
