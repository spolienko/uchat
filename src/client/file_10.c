#include "client.h"


int mx_check_on_cmd(char *str) {
    char *strr = mx_get_cmd(str);
    if (!strcmp(strr, "|love|"))
        return 1;
    if (!strcmp(strr, "|beuty|"))
        return 2;
    if (!strcmp(strr, "|++++|"))
        return 3;
    if (!strcmp(strr, "|sadness|"))
        return 4;
    if (!strcmp(strr, "|danger|"))
        return 5;
    if (!strcmp(strr, "|sad_cat|"))
        return 6;
    if (!strcmp(strr, "|????|"))
        return 7;
    if (!strcmp(strr, "|hello|"))
        return 8;
    return 0;
}



char *mx_what_return(int gg) {
    if (gg == 0)
        return "|love|";
    if (gg == 1)
        return "|beuty|";
    if (gg == 2)
        return "|++++|";
    if (gg == 3)
        return "|sadness|";
    if (gg == 4)
        return "|danger|";
    if (gg == 5)
        return "|sad_cat|";
    if (gg == 6)
        return "|????|";
    if (gg == 7)
        return "|hello|";
    return "err";
} 

void mx_sen0(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = mx_what_return(0);
        char *m = malloc(strlen(message) + 1);

        strcpy(m, message);
        cJSON *send = cJSON_CreateObject();
        char *res;

        cJSON_AddStringToObject(send, "kind", "msg");
        cJSON_AddStringToObject(send, "login", s->h->login);
        cJSON_AddStringToObject(send, "msg", m);
        res = cJSON_Print(send);
        tls_write(s->c->tls, res, strlen(res) + 1);
        gtk_entry_set_text(GTK_ENTRY(s->h->v_main_e), "");
    }
    (void)widget;
}

void mx_sen1(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = mx_what_return(1);
        char *m = malloc(strlen(message) + 1);

        strcpy(m, message);
        cJSON *send = cJSON_CreateObject();
        char *res;

        cJSON_AddStringToObject(send, "kind", "msg");
        cJSON_AddStringToObject(send, "login", s->h->login);
        cJSON_AddStringToObject(send, "msg", m);
        res = cJSON_Print(send);
        tls_write(s->c->tls, res, strlen(res) + 1);
        gtk_entry_set_text(GTK_ENTRY(s->h->v_main_e), "");
    }
    (void)widget;
}

void mx_sen2(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = mx_what_return(2);
        char *m = malloc(strlen(message) + 1);

        strcpy(m, message);
        cJSON *send = cJSON_CreateObject();
        char *res;

        cJSON_AddStringToObject(send, "kind", "msg");
        cJSON_AddStringToObject(send, "login", s->h->login);
        cJSON_AddStringToObject(send, "msg", m);
        res = cJSON_Print(send);
        tls_write(s->c->tls, res, strlen(res) + 1);
        gtk_entry_set_text(GTK_ENTRY(s->h->v_main_e), "");
    }
    (void)widget;
}

