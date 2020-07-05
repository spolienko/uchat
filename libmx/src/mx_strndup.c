#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    char *str_new;
    size_t len = (n >= (size_t)mx_strlen(s1)) ? (size_t)mx_strlen(s1) : n;

    str_new = mx_strnew(len);
    if (str_new == NULL)
        return NULL;
    return str_new ? mx_strncpy(str_new, s1, len) : NULL;
}

