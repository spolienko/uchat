#include "libmx.h"

int mx_strcmp(const char *s1, const char *s2) {
    int i = 0;

    while (s1[i] == s2[i]) {
        if (s1[i] == '\0')
            return 0;
        i++;
    }
    return (unsigned char) s1[i] - (unsigned char) s2[i];
}

