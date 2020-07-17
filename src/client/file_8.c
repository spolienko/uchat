#include "client.h"

void mx_do_s(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = (char *)gtk_entry_get_text(GTK_ENTRY(s->h->v_main_e));
    
        if (!message || !*message )
            return;
        if (strlen(message) < 110 && strlen(message) > 0) {
            char *res = mx_parsing_mes(message, s);
            if (res != NULL)
                tls_write(s->c->tls, res, strlen(res) + 1);
        }
        else
            printf("\n");
        gtk_entry_set_text(GTK_ENTRY(s->h->v_main_e), "");
    }
    (void)widget;
}

void mx_drop_sesion(t_s *s) {
    cJSON *send = cJSON_CreateObject();
    char *res;

    cJSON_AddStringToObject(send, "kind", "drop_sesion");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddNumberToObject(send, "drop_id", s->h->was_connect);
    res = cJSON_Print(send);
    tls_write(s->c->tls, res, strlen(res) + 1);
}

void mx_set_class_for_help(t_inf_row *inf) {
    inf->c_v_body = gtk_widget_get_style_context(inf->v_body);
    gtk_style_context_add_class(inf->c_v_body, "pading_left_100");
}

void init_help(t_inf_row *inf, t_s *s) {
    char *str = mx_help_str(s);

    inf->v_row = gtk_list_box_row_new();
    gtk_list_box_insert((GtkListBox *)s->h->v_listbox, inf->v_row, s->h->v_n);
    s->h->v_n++;
    inf->v_hrow = gtk_box_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(inf->v_row), inf->v_hrow);
    inf->v_body = gtk_label_new(str);
    gtk_box_pack_start(GTK_BOX(inf->v_hrow), inf->v_body, FALSE, FALSE, 0);
    gtk_widget_set_size_request(inf->v_body, 250, 10);
    gtk_label_set_xalign((GtkLabel *)inf->v_body, 0.1);
    mx_set_class_for_help(inf);
}

int mx_show_widget(GtkWidget *widget) {
    gtk_widget_show_all(widget);
    return 0;
}

