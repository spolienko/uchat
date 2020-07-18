#include "client.h"


void mx_init_while_login(t_s *s) {
    while (true) {
        bzero(s->c->bufs, 1000);
        bzero(s->c->bufc, 1000);
        poll(s->c->pfd, 2, -1);
        if (s->c->pfd[1].revents & POLLIN) {
            if ((s->c->rc = tls_read(s->c->tls, s->c->bufs, 1000)) <= 0) 
                break;
            mx_work_in_while(s);
            return;
        }  
    }
}

void mx_do_logining(GtkWidget *widget, t_s *s) {
    if (mx_check_on_input(widget, s))
        return;
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "login");
    cJSON_AddStringToObject(send, "login", s->l->login);
    cJSON_AddStringToObject(send, "pasword", s->l->pass);
    char *res = cJSON_Print(send);

    if (mx_init_server(s, s->l->argv))
        mx_closeApp(s->l->win, s);
    tls_write(s->c->tls, res, strlen(res) + 1);
    mx_init_while_login(s);
}

gboolean mx_check_logining(t_s *s) {
    if (s->l->login_in) {
        s->l->login_in = 0;
        gtk_widget_hide(s->l->win);
        mx_init_chatt(s);
        return G_SOURCE_REMOVE;
    }
    return G_SOURCE_CONTINUE;
}

void mx_init_logining_1(t_s *s) {
    s->l->login_in = 0;
    s->l->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    s->l->main_l = gtk_label_new("Uchat");
    s->l->user_lbl = gtk_label_new("Login:");
    s->l->pass_lbl = gtk_label_new("Password:");
    s->l->e_lbl = gtk_label_new("");
    s->l->user_ety = gtk_entry_new();
    s->l->pass_ety = gtk_entry_new();
    s->l->ok_btn = gtk_button_new_with_label("Enter");
    gtk_entry_set_text(GTK_ENTRY(s->l->user_ety), "admin");
    gtk_entry_set_text(GTK_ENTRY(s->l->pass_ety), "admin");
    s->l->vbox = gtk_box_new(TRUE, 0);
    s->l->m_lbl_b = gtk_box_new(TRUE, 10);
    s->l->u_box = gtk_box_new(FALSE, 10);
    s->l->p_box = gtk_box_new(FALSE, 10);
    s->l->e_box = gtk_box_new(TRUE, 0);
    s->l->ok_btn_b = gtk_box_new(TRUE, 0);
    s->l->SP = gtk_css_provider_new();
}

void mx_init_logining_2(t_s *s) {
    gtk_window_set_position(GTK_WINDOW(s->l->win), GTK_WIN_POS_CENTER_ALWAYS);
    gtk_entry_set_visibility(GTK_ENTRY(s->l->pass_ety), FALSE);
    gtk_window_set_resizable (GTK_WINDOW(s->l->win), FALSE);
    gtk_css_provider_load_from_path(s->l->SP, "src/client/theme.css", NULL);
    gtk_style_context_add_provider_for_screen( gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(s->l->SP),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_set_title(GTK_WINDOW(s->l->win), "Uchat");
    g_signal_connect(G_OBJECT(s->l->win), "destroy",
        G_CALLBACK(gtk_main_quit), s);
    s->l->c_window = gtk_widget_get_style_context(s->l->win);
    s->l->c_main_label = gtk_widget_get_style_context(s->l->main_l);
    s->l->c_user_lbl = gtk_widget_get_style_context(s->l->user_lbl);
    s->l->c_pass_lbl = gtk_widget_get_style_context(s->l->pass_lbl);
    s->l->c_user_ety = gtk_widget_get_style_context(s->l->user_ety);
    s->l->c_pass_ety = gtk_widget_get_style_context(s->l->pass_ety);
    s->l->c_error_label = gtk_widget_get_style_context(s->l->e_lbl);
    s->l->c_ok_button = gtk_widget_get_style_context(s->l->ok_btn);
}

