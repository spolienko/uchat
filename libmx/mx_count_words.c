#include "libmx.h"

int mx_count_words(const char *str, char c) {
    int count = 0;
    int flag = 0;
    int len = mx_strlen(str);

    if (str && c) {
        for (int i = 0; i < len; i++) {
            if (str[i] == c)
                flag = 0;
            else if ((str[i] != c) && (flag == 0)) {
                flag = 1;
                count++;
            }
            else
                flag = 1;
        }
    }
    return count;
}

