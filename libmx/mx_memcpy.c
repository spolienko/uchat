#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    char *p_dst = dst;
    const char *p_src = src;

    while (n--)
        *p_dst++ = *p_src++;
    return dst;
}

