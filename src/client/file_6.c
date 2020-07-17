#include "client.h"

char *mx_change_pass_creating(char *m, t_s *s) {
    cJSON *send = cJSON_CreateObject();
    char *new_pass = mx_get_new_pass(m);

    if (strlen(new_pass) > 30) {
        cJSON_AddStringToObject(send, "kind", "new_password");
        cJSON_AddStringToObject(send, "who_change", s->h->login);
        cJSON_AddStringToObject(send, "new_pass", new_pass);
    }
    return cJSON_Print(send);
}

int mx_is_have_matyki(char *m, t_s *s) {
    if (strlen(m) == 3) {
        if (m[0] == '|' && m[1] == 'm' && m[2] == '|') {
            if (s->h->is_output_matyki)
                s->h->is_output_matyki = 0;
            else 
                s->h->is_output_matyki = 1;
            return 1;
        }
        return 0;
    }
    return 0;
}

int mx_is_have_sound(char *m, t_s *s) {
    if (strlen(m) == 3) {
        if (m[0] == '|' && m[1] == 's' && m[2] == '|') {
            if (s->h->is_output_sound)
                s->h->is_output_sound = 0;
            else 
                s->h->is_output_sound = 1;
            return 1;
        }
        return 0;
    }
    return 0;
}

int mx_is_have_visual(char *m, t_s *s) {
    if (strlen(m) == 3) {
        if (m[0] == '|' && m[1] == 'v' && m[2] == '|') {
            if (s->h->is_output_visual)
                s->h->is_output_visual = 0;
            else 
                s->h->is_output_visual = 1;
            return 1;
        }
        return 0;
    }
    return 0;
}


int mx_is_have_clean_history(char *m) {
    if (strlen(m) == 3) {
        if (m[0] == '|' && m[1] == 'c' && m[2] == '|') {
            return 1;
        }
        return 0;
    }
    return 0;
}
