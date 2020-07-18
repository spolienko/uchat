#include "libmx.h"

char *mx_strnew(const int size) {
    char *str = NULL;

    if (size < 0)
        return str;
    if ((str = (char*) malloc(size + 1)) != NULL)
        for (int i = 0; i < size + 1; i++)
            str[i] = '\0';
    return str;
}

