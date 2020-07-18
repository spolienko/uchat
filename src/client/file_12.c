#include "client.h"


void mx_init_row(t_row *row, t_info *inf, t_s *s) {
    row->v_row = gtk_list_box_row_new();
    gtk_list_box_insert((GtkListBox *)s->h->v_listbox, row->v_row, s->h->v_n);
    s->h->v_n++;
    row->v_hrow = gtk_box_new(FALSE, 0);
    row->v_taa_box = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(row->v_row), row->v_hrow);
    row->v_author = gtk_label_new(inf->author);
    gtk_box_pack_start(GTK_BOX(row->v_taa_box), row->v_author,
                       FALSE, FALSE, 0);
    gtk_widget_set_size_request(row->v_author, 250, 30);
    row->v_time = gtk_label_new(inf->timebuf);
    gtk_box_pack_start(GTK_BOX(row->v_taa_box), row->v_time, FALSE,
                               FALSE, 0);
    gtk_widget_set_size_request(row->v_time, 250, 30);
    gtk_container_add(GTK_CONTAINER(row->v_hrow), row->v_taa_box);
}


void mx_delete(GtkWidget *widget, t_for_click *c) {
    if (c->s->h->can_do_msg) {
        cJSON *send = cJSON_CreateObject();

        cJSON_AddStringToObject(send, "kind", "delete");
        cJSON_AddStringToObject(send, "login", c->s->h->login);
        cJSON_AddNumberToObject(send, "id", c->inf->id);
        char *res = cJSON_Print(send);

        c->s->h->can_do_msg = 0;
        tls_write(c->s->c->tls, res, strlen(res) + 1);
    }
    (void)widget;
}

void mx_set_class_for_X(t_row *row, t_info *inf, t_s *s) {
    row->c_v_bt_del = gtk_widget_get_style_context(row->v_bt_del);
    gtk_style_context_add_class(row->c_v_bt_del, "X");
    (void)inf;
    (void)s;
}

gboolean mx_check_editing(t_for_click *c) {  
    if (c->s->h->d_id == c->inf->id || c->s->h->is_drop_all_messages) {
        gtk_container_remove((GtkContainer *)c->s->h->v_listbox,
            c->row->v_row);
        c->s->h->d_id = -2;
        return G_SOURCE_REMOVE;
    }
    if (c->s->h->e_id == c->inf->id && c->row->is_sticker) {
        gtk_label_set_text((GtkLabel *)c->row->v_body, c->s->h->edit_txt);
        return G_SOURCE_CONTINUE;
    }
    return G_SOURCE_CONTINUE;
}

void mx_print_X(t_row *row, t_info *inf, t_s *s) {
    t_for_click *c = malloc(sizeof(t_for_click));

    c->row = row;
    c->inf = inf;
    c->s = s;
    if (!strcmp(inf->author, s->h->login)) {
        row->v_bt_del = gtk_button_new_with_label("X");
        gtk_widget_set_name(row->v_bt_del, "X");
        gtk_box_pack_start(GTK_BOX(row->v_hrow), 
        row->v_bt_del, FALSE, FALSE, 0);
        mx_set_class_for_X(row, inf, s);
        g_signal_connect(G_OBJECT(row->v_bt_del), "clicked",
            G_CALLBACK(mx_delete), c);
    }   
    g_timeout_add(50, (GSourceFunc)mx_check_editing, c);
}
