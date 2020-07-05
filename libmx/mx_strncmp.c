#include "libmx.h"

int mx_strncmp(const char *s1, const char *s2, int len_s2) {
    for (int i = 0; i < len_s2; i++) {
        if (s1[i] != s2[i])
           return (unsigned char) s1[i] - (unsigned char) s2[i];
    }
    return 0;
}

