#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace){
    int diff;
    char *res;

    if (!str || !sub || !replace)
        return NULL;
    diff = mx_strlen(sub) - mx_strlen(replace);
    diff = diff < 0 ? -diff : diff;
    res = mx_strnew(mx_strlen(str) + mx_count_substr(str, sub) * diff);
    for (int i = 0, k = 0; i < mx_strlen(str); i++) {
        if (!mx_get_substr_index(&str[i], sub)) {
            for (int j = 0; j < mx_strlen(replace); j++, k++)
                res[k] = replace[j];
            i += mx_strlen(sub) - 1;
        }
        else {
            res[k] = str[i];
            k++;
        }
    }
    return res;
}
