#include "libmx.h"

void mx_str_reverse(char *s) {
    if (!s || !*s)
        return;

    char *pa = s;
    int len = mx_strlen(s);

    for (int i = 0; i < (len / 2); i++)
        mx_swap_char((pa + i), (pa + len - 1 - i));
}

