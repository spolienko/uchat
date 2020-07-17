#include "client.h"



int mx_is_have_cmd(char *str) {
    if (str[0] == '|' && (str[2] == '|' || str[3] == '|' 
        || str[4] == '|' || str[1] == '|'))
        return 1;
    return 0;
}

static int arr_size(char **arr) {
    int result = 0;

    while (*arr) {
        result++;
        arr++;
    }
    return result;
}

char *mx_strncat(char *restrict s1, const char *restrict s2, size_t n) {
    char *save = s1;

    s1 += mx_strlen(s1);
    mx_strncpy(s1, s2, n);
    return save;
}




char *mx_replace_sub(const char *str, const char *sub,
                     const char *replace) {
    int subs = mx_count_substr(str, sub);
    int subs_length = mx_strlen(sub) * subs;
    int replace_length = mx_strlen(replace) * subs;
    char *result = NULL;
    int index = 0;

    if (!*str || !*sub) {
        return NULL;
    }
    result = mx_strnew(mx_strlen(str) - subs_length + replace_length);
    while ((index = mx_get_substr_index(str, sub)) != -1) {
        mx_strncat(result, str, index);
        mx_strcat(result, replace);
        str += index + mx_strlen(sub);
    }
    mx_strcat(result, str);
    return result;
}

char *mx_get_without_mats(char *new_str) {
    char *arr_eng_mats[1024] = {"fuck", "dick", "suck", "shut", "cocks", 
        "condom", "fart", "pussy", "ass", "bitch", "shit"};
    char *arr_rus_mats[1024] = {"хуй", "гавно", "лох", "сука", "пососи",
        "ретард", "pidor", "гамосек", "сосунок", "даун", "аутист", "блядь",
        "ебать", "тупо", "шлюха", "деби", "гей", "отбитый", "конча"};

    for (int i = 0; i < arr_size(arr_eng_mats); i++) {
        new_str = mx_replace_sub(new_str, arr_eng_mats[i], "***");
    }
    for (int i = 0; i < arr_size(arr_rus_mats); i++) {
        new_str = mx_replace_sub(new_str, arr_rus_mats[i], "***");
    }
    sprintf(new_str, "%s", new_str);
    return new_str;
}

