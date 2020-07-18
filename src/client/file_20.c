#include "client.h"


gboolean mx_set_cant_delete_all_mes(t_s *s) {
    s->h->is_drop_all_messages = 0;
    return G_SOURCE_REMOVE;
}

void mx_drop_all_messages(t_s *s) {
    s->h->is_drop_all_messages = 1;
    g_timeout_add(2000, (GSourceFunc)mx_set_cant_delete_all_mes, s);
}

char *mx_create_privat_message_body(cJSON *msg) {
    char *sss = mx_strneww(1024);
    char *who_send = cJSON_GetObjectItemCaseSensitive(msg,
        "who_send")->valuestring;
    char *msgg = cJSON_GetObjectItemCaseSensitive(msg,
        "msg")->valuestring;

    sprintf(sss, "%s: %s", who_send, msgg);
    return sss;
}

void mx_create_privat_mes(t_s *s, cJSON *msg) {
    char *who_get = cJSON_GetObjectItemCaseSensitive(msg, 
        "to_user")->valuestring;

    if(!strcmp(who_get, s->h->login)) {
        t_inf_row *inf = malloc(sizeof(t_inf_row));
        char *str = mx_create_privat_message_body(msg);

        inf->v_row = gtk_list_box_row_new();
        gtk_list_box_insert((GtkListBox *)s->h->v_listbox, inf->v_row, 
            s->h->v_n);
        s->h->v_n++;
        inf->v_hrow = gtk_box_new(FALSE, 0);
        gtk_container_add(GTK_CONTAINER(inf->v_row), inf->v_hrow);
        inf->v_body = gtk_label_new(str);
        gtk_box_pack_start(GTK_BOX(inf->v_hrow), inf->v_body, 0, FALSE, 0);
        gtk_widget_set_size_request(inf->v_body, 250, 50);
        gtk_label_set_xalign((GtkLabel *)inf->v_body, 0.1);
        mx_set_class_for_help(inf);
    }
    g_idle_add ((int (*)(void *))mx_show_widget, s->h->v_window);
}

void mx_check_mesage_from_serv(t_s *s, cJSON *msg) {
    char *ch = cJSON_GetObjectItemCaseSensitive(msg, "kind")->valuestring;

    if (!strcmp(ch, "msg"))
        mx_create_msg(s, msg);
    if (!strcmp(ch, "delete"))
        mx_delete_msg(s, msg);
    if (!strcmp(ch, "connection"))
        mx_init_connect_msg(s, msg);
    if (!strcmp(ch, "drop_user"))
        mx_droping_account(s, msg);
    if (!strcmp(ch, "edit"))
        mx_edit_mess(s, msg);
    if (!strcmp(ch, "drop_all_mess"))
        mx_drop_all_messages(s);
    if (!strcmp(ch, "privat_mess"))
        mx_create_privat_mes(s, msg);
}

