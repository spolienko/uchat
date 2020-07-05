#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    int len_h = mx_strlen(haystack);
    int len_n = mx_strlen(needle);

    if (needle == NULL)
        return (char *) haystack;

    for (int i = 0; i < len_h; i++, haystack++) {
        if (mx_strncmp(haystack, needle, len_n) == 0)
            return (char *) haystack;
    }
    return NULL;
}

