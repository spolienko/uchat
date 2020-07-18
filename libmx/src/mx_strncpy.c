#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    int len_src = mx_strlen(src);

    for (int i = 0; i < len; i++)
        dst[i] = (i <= len_src) ? src[i] : '\0';
    return dst;
}

