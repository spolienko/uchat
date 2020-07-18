#include "client.h"


int mx_is_have_drop(char *m) {
    int i[2] = {0, 0};

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|')
                i[1] = gg;
            if (m[gg] == '\0')
                return 0;
        }
        if (strlen(m) > 4)
            if (m[1] == 'k' &&  m[2] == '_') {
                return 1;
            }
    }
    return 0;
}

char *mx_get_user_drop(char *m) {
    int i[2] = {0, 0};
    char *sss = mx_strneww(1000);

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|') {
                i[1] = gg;
                break;
            }
        }
    }
    sprintf(sss, "%s", strndup(m + 3, i[1] - 3));
    return sss;
}

char *mx_drop_creating(char *m, t_s *s) {
    cJSON *send = cJSON_CreateObject();
    char *user_drop = mx_get_user_drop(m);
    
    cJSON_AddStringToObject(send, "kind", "drop_user");
    cJSON_AddStringToObject(send, "admin", s->h->login);
    cJSON_AddStringToObject(send, "drop_user", user_drop);
    return cJSON_Print(send);
}

int mx_is_have_change_pass(char *m) {
    int i[2] = {0, 0};

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|') {
                i[1] = gg;
                break;
            }
            if (m[gg] == '\0')
                return 0;
        }
        if (strlen(m) > 4)
            if (m[1] == 'p' &&  m[2] == '_') {
                return 1;
            }
    }
    return 0;
}

char *mx_get_new_pass(char *m) {
    int i[2] = {0, 0};
    char *sss = mx_strneww(1000);

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|') {
                i[1] = gg;
                break;
            }
        }
    }
    sprintf(sss, "%s", strndup(m + 3, i[1] - 3));
    return sss;
}

