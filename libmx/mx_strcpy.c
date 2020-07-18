#include "libmx.h"

char *mx_strcpy(char *dst, const char *src) {
    for (int i = 0; (dst[i] = src[i]) != '\0'; i++);
    return dst;
}

