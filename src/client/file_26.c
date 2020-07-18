#include "client.h"


void mx_7_chat_init(t_s *s) {
    gtk_container_add(GTK_CONTAINER(s->h->v_scroll), s->h->v_listbox);
    g_signal_connect(s->h->v_window,"destroy",G_CALLBACK(mx_closeApp2), s);
    gtk_scrolled_window_set_max_content_width(
        (GtkScrolledWindow *)s->h->v_scroll, 500);
    gtk_window_set_title(GTK_WINDOW(s->h->v_window), (const gchar *)"uchat");
    gtk_widget_show_all((GtkWidget *)s->h->v_window);
}

void mx_send_conection(t_s *s) {
    cJSON *send = cJSON_CreateObject();
    char *res;

    cJSON_AddStringToObject(send, "kind", "connection");
    res = cJSON_Print(send);
    tls_write(s->c->tls, res, strlen(res) + 1);
}

void mx_init_chatt(t_s *s) {
    mx_1_chat_init(s);
    mx_2_chat_init(s);
    mx_3_chat_init(s);
    mx_4_chat_init(s);
    mx_5_chat_init(s);
    mx_6_chat_init(s);
    mx_7_chat_init(s);
    mx_send_conection(s);
    gtk_window_set_position(GTK_WINDOW(s->h->v_window),
        GTK_WIN_POS_CENTER_ALWAYS); 
    pthread_t thread_input;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int tc = pthread_create(&thread_input, &attr, 
        mx_watcher_thread, (void *)s);
    
    if (tc != 0)
        printf("pthread_create error = %s\n", strerror(tc));    
}



int mx_check_on_input(GtkWidget *widget, t_s *s) {
    (void)widget;
    const gchar *login = gtk_entry_get_text(GTK_ENTRY(s->l->user_ety));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(s->l->pass_ety));

    if (!login || !*login) {
        gtk_label_set_text((GtkLabel *)s->l->e_lbl, "Login is empty");
        return 1;
    }
    if (!password || !*password) {
        gtk_label_set_text((GtkLabel *)s->l->e_lbl, "Password is empty");
        return 1;
    }
    if (strlen(password) > 30 || strlen(login) > 30) {
        gtk_label_set_text((GtkLabel *)s->l->e_lbl, "Something very long");
        return 1;
    }
    s->l->login = (char *)login;
    s->l->pass = (char *)password;
    return 0;
}




void mx_work_in_while(t_s *s) {
    cJSON *msg = cJSON_Parse(s->c->bufs);

    s->l->login_in = cJSON_GetObjectItemCaseSensitive(msg,
        "status")->valueint;
    if (!s->l->login_in) {
        gtk_label_set_text((GtkLabel *)s->l->e_lbl, "Error");
        return;
    }
    s->l->lang = cJSON_GetObjectItemCaseSensitive(msg,
        "lang")->valuestring;
    s->l->theme = cJSON_GetObjectItemCaseSensitive(msg,
        "tema")->valuestring;
}


