#include "client.h"


void mx_init_logining_3(t_s *s) {
    gtk_widget_set_size_request(s->l->user_lbl, 100, 50);
    gtk_widget_set_size_request(s->l->pass_lbl, 100, 50);
    gtk_widget_set_size_request(s->l->user_ety, 200, 50);
    gtk_widget_set_size_request(s->l->pass_ety, 200, 50);
    gtk_widget_set_size_request(s->l->ok_btn, 200, 50);
    gtk_style_context_add_class(s->l->c_window, "lw");
    gtk_style_context_add_class(s->l->c_main_label, "bl");
    gtk_style_context_add_class(s->l->c_user_lbl, "bl");
    gtk_style_context_add_class(s->l->c_pass_lbl, "bl");
    gtk_style_context_add_class(s->l->c_user_ety, "bl");
    gtk_style_context_add_class(s->l->c_pass_ety, "bl");
    gtk_style_context_add_class(s->l->c_ok_button, "bl");
    gtk_style_context_add_class(s->l->c_ok_button, "ok_btn");
    gtk_style_context_add_class(s->l->c_main_label, "main_l");
    gtk_style_context_add_class(s->l->c_error_label, "error");
    gtk_style_context_add_class(s->l->c_user_ety, "lent");
    gtk_style_context_add_class(s->l->c_pass_ety, "lent");
}

void mx_init_logining_4(t_s *s) {
    gtk_box_pack_start(GTK_BOX(s->l->m_lbl_b), s->l->main_l, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->u_box), s->l->user_lbl, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->u_box), s->l->user_ety, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->p_box), s->l->pass_lbl, FALSE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->p_box), s->l->pass_ety, FALSE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->e_box), s->l->e_lbl, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(s->l->ok_btn_b), s->l->ok_btn, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->vbox), s->l->m_lbl_b, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->vbox), s->l->u_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->vbox), s->l->p_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->vbox), s->l->e_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->vbox), s->l->ok_btn_b, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(s->l->ok_btn), "clicked",
                     G_CALLBACK(mx_do_logining), s);
    gtk_container_add(GTK_CONTAINER(s->l->win), s->l->vbox);
    g_timeout_add(50, (GSourceFunc)mx_check_logining, s);
    gtk_widget_show_all(s->l->win);
    gtk_main();
}

