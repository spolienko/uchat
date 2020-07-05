#include "libmx.h"

char *mx_strdup(const char *s1) {
    char *str_new = mx_strnew(mx_strlen(s1));

    if (str_new == NULL)
        return NULL;
    return str_new ? mx_strcpy(str_new, s1) : NULL;
}

