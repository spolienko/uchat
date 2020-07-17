#include "client.h"

char *mx_clean_history( t_s *s) {
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "clean_chat");
    cJSON_AddStringToObject(send, "who_clean", s->h->login);
    return cJSON_Print(send);
}

char *mx_parsing_normal_mess(char *m, t_s *s) {
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "msg");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "msg", m);
    return cJSON_Print(send);
}


int mx_is_have_privat_message(char *m) {
    int i[2] = {0, 0};

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|')
                i[1] = gg;
            if (m[gg] == '\0')
                return 0;
        }
        if (strlen(m) > 4)
            if (m[1] == 'x' &&  m[2] == '_') {
                return 1;
            }
    }
    return 0;
}

char *mx_get_user_for_privat(char *m) {
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


char *mx_create_privat_message(char *m, t_s *s) {
    cJSON *send = cJSON_CreateObject();
    char *user_for_privat = mx_get_user_for_privat(m);
    char *msg = mx_get_new_body_e(m);
    
    cJSON_AddStringToObject(send, "kind", "privat_mess");
    cJSON_AddStringToObject(send, "who_send", s->h->login);
    cJSON_AddStringToObject(send, "to_user", user_for_privat);
    cJSON_AddStringToObject(send, "msg", msg);
    return cJSON_Print(send);
}
