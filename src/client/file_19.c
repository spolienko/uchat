#include "client.h"


void mx_delete_msg(t_s *s, cJSON *msg) {
    s->h->d_id = cJSON_GetObjectItemCaseSensitive(msg, "id")->valueint;
}

void mx_edit_mess(t_s *s, cJSON *msg) {
    s->h->e_id = cJSON_GetObjectItemCaseSensitive(msg, "id")->valueint;
    s->h->edit_txt = cJSON_GetObjectItemCaseSensitive(msg,
        "msg")->valuestring;
}

void mx_init_connect_msg(t_s *s, cJSON *msg) {
    s->h->was_connect = cJSON_GetObjectItemCaseSensitive(msg,
        "conn_id")->valueint;
}

void mx_drop_acc(GtkWidget *widget, t_s *s) {
    (void)widget;
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "drop_acc");
    cJSON_AddStringToObject(send, "login", s->h->login);
    char *res = cJSON_Print(send);

    tls_write(s->c->tls, res, strlen(res) + 1);
    mx_closeApp2(s->h->v_window, s);
}



void mx_droping_account(t_s *s, cJSON *msg) {
    s->h->drop_acc = cJSON_GetObjectItemCaseSensitive(msg,
        "drop_user")->valuestring;

    if (!strcmp(s->h->drop_acc, s->h->login))
        mx_drop_acc(NULL, s);
}

