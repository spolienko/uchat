#include "libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    if (!s1 && !s2)
        return NULL;
    else if (!s1 && s2)
        return mx_strdup(s2);
    else if (s1 && !s2)
        return mx_strdup(s1);
    else {
        char * str = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
        mx_strcpy(str, s1);
     //   mx_strcpy((str + mx_strlen(s1)), "");
        mx_strcpy((str + mx_strlen(s1)), s2);
        return str ? str : NULL;
    }
}

