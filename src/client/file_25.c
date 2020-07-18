#include "client.h"



void mx_set_russ(t_s *s) {
    gtk_button_set_label((GtkButton *)s->h->v_l_btn_ru, "РУС");
    gtk_button_set_label((GtkButton *)s->h->v_l_btn_en, "АНГ");
    gtk_button_set_label((GtkButton *)s->h->v_l_btn_rm, "Удалить");
    gtk_button_set_label((GtkButton *)s->h->v_bt_e, "Отправить");
    gtk_button_set_label((GtkButton *)s->h->v_bt_inf, "Информация");
    gtk_button_set_label((GtkButton *)s->h->v_bt_lik, "Любовь");
    gtk_button_set_label((GtkButton *)s->h->v_bt_aut, "Красота");
    gtk_button_set_label((GtkButton *)s->h->v_bt_s1, "Хорошо");
    gtk_button_set_label((GtkButton *)s->h->v_bt_s2, "Грусть");
    gtk_button_set_label((GtkButton *)s->h->v_bt_s3, "Опасность");
    gtk_button_set_label((GtkButton *)s->h->v_bt_s4, "Грустный Кот");
    gtk_button_set_label((GtkButton *)s->h->v_bt_s5, "Вопрос?");
    gtk_button_set_label((GtkButton *)s->h->v_bt_s6, "Привет");
    s->h->lang = "rus";
}

void mx_set_en(GtkWidget *widget, t_s *s) {
    (void)widget;
    mx_set_engl(s);
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "ui");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "tema", s->h->theme);
    cJSON_AddStringToObject(send, "lang", "eng");
    char *res = cJSON_Print(send);

    tls_write(s->c->tls, res, strlen(res) + 1);
}

void mx_set_ru(GtkWidget *widget, t_s *s) {
    (void)widget;
    mx_set_russ(s);
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "ui");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "tema", s->h->theme);
    cJSON_AddStringToObject(send, "lang", "rus");
    char *res = cJSON_Print(send);

    tls_write(s->c->tls, res, strlen(res) + 1);
}

void mx_5_chat_init(t_s *s) {
    s->h->d_id = -2;
    s->h->is_output_matyki = 0;
    s->h->is_output_sound = 1;
    s->h->is_output_visual = 0;
    s->h->is_drop_all_messages = 0;
    g_signal_connect(G_OBJECT(s->h->v_l_btn_en), "clicked", 
        G_CALLBACK(mx_set_en), s);
    g_signal_connect(G_OBJECT(s->h->v_l_btn_ru), "clicked",
        G_CALLBACK(mx_set_ru), s);
    g_signal_connect(G_OBJECT(s->h->v_t_btn_b), "clicked",
        G_CALLBACK(mx_set_b), s);
    g_signal_connect(G_OBJECT(s->h->v_t_btn_w), "clicked", 
        G_CALLBACK(mx_set_w), s);
    g_signal_connect(G_OBJECT(s->h->v_l_btn_rm), "clicked", 
        G_CALLBACK(mx_drop_acc), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_inf), "clicked", 
        G_CALLBACK(mx_inf), s);
}

void mx_6_chat_init(t_s *s) {
    g_signal_connect(G_OBJECT(s->h->v_bt_lik), "clicked", 
        G_CALLBACK(mx_sen0), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_aut), "clicked", 
        G_CALLBACK(mx_sen1), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_s1), "clicked", 
        G_CALLBACK(mx_sen2), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_s2), "clicked",
        G_CALLBACK(mx_sen3), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_s3), "clicked", 
        G_CALLBACK(mx_sen4), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_s4), "clicked",
        G_CALLBACK(mx_sen5), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_s5), "clicked",
        G_CALLBACK(mx_sen6), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_s6), "clicked",
        G_CALLBACK(mx_sen7), s);
}


