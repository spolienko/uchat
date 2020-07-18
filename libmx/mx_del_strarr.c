#include "libmx.h"

void mx_del_strarr(char ***arr) {
    if (arr == NULL)
        return;

    char ***p = arr;
    char **pp = *arr;
    while (**p != NULL) {
        mx_strdel(*p);
        (*p)++;
    }
    free(pp);
    *arr = NULL;
}
