#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int count = 0;
    int len_sub = mx_strlen(sub);
    int len_str = mx_strlen(str);
    const char *p = str;
    int a;

    if (!sub || !str)
        return -1;

    while (p < (str + len_str)) {
        a = mx_get_substr_index(p, sub);
        if (a >= 0) {
            count++;
            p = (p + a + len_sub);
        }
        else
            break;
    }
    return count;
}

