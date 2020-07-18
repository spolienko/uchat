#include "libmx.h"

char **mx_strsplit(const char *s, char c) {
    if (!s)
        return NULL;
    int count_words = mx_count_words(s, c);
    char **arr_words = (char **)malloc((count_words + 1 ) * sizeof(char*));
    int len_w = 0;

    for (int j = 0; *s != '\0'; s++) {
        if (*s != c) {
            len_w++;
            if (*(s + 1) == '\0') {
                arr_words[j] = mx_strncpy(mx_strnew(len_w), (s - len_w + 1) ,len_w);
                break;
            }
        }
        else if (*s == c) {
            if (len_w == 0);
            else if (len_w != 0) {
                arr_words[j] = mx_strncpy(mx_strnew(len_w), (s - len_w) ,len_w);
                len_w =  0;
                j++;
            }
        }
    }
    arr_words[count_words] = NULL;
    return (arr_words) ? arr_words : NULL;
}

