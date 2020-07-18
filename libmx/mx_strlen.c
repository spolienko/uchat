#include "libmx.h"

int mx_strlen(const char *s) {
    int len = 0;

    while(*s++)
        len++;
    return len;
}

