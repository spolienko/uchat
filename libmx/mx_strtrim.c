#include "libmx.h"

char *mx_strtrim(const char *str) {
    int i = 0;
    int j;
    char *n;

    if (!str)
        return NULL;
    j = mx_strlen(str) - 1;
    while (mx_isspace(str[i]))
        i++;
    while (mx_isspace(str[j]))
        j--;
    if (i <= j) {
        n = mx_strncpy(mx_strnew(j + 1 - i), &str[i], j + 1 - i);
        return n;
    }
    else
        return malloc(0);
}
