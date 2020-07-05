#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    char *p = mx_strstr(str, sub);

    if (!str || !sub)
        return -2;

    else if (p == NULL)
        return -1;
    else
        return p - str;
}

