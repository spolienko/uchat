#include "client.h"



void mx_add_class_white(t_s *s) {
    gtk_style_context_add_class(s->h->c_v_l_btn_ru, "white");
    gtk_style_context_add_class(s->h->c_v_l_btn_en, "white");
    gtk_style_context_add_class(s->h->c_v_l_btn_rm, "white");
    gtk_style_context_add_class(s->h->c_v_scroll, "white");
    gtk_style_context_add_class(s->h->c_v_main_e, "white");
    gtk_style_context_add_class(s->h->c_v_bt_e, "white");
    gtk_style_context_add_class(s->h->c_v_bt_like, "white");
    gtk_style_context_add_class(s->h->c_v_bt_aut, "white");
    gtk_style_context_add_class(s->h->c_v_bt_info, "white");
    gtk_style_context_add_class(s->h->c_v_bt_s1, "white");
    gtk_style_context_add_class(s->h->c_v_bt_s2, "white");
    gtk_style_context_add_class(s->h->c_v_bt_s3, "white");
    gtk_style_context_add_class(s->h->c_v_bt_s4, "white");
    gtk_style_context_add_class(s->h->c_v_bt_s5, "white");
    gtk_style_context_add_class(s->h->c_v_bt_s6, "white");
    gtk_style_context_add_class(s->h->c_v_t_btn_b, "white");
    gtk_style_context_add_class(s->h->c_v_t_btn_w, "white");
}

void mx_add_class_black(t_s *s) {
    gtk_style_context_add_class(s->h->c_v_l_btn_ru, "black");
    gtk_style_context_add_class(s->h->c_v_l_btn_en, "black");
    gtk_style_context_add_class(s->h->c_v_l_btn_rm, "black");
    gtk_style_context_add_class(s->h->c_v_scroll, "black");
    gtk_style_context_add_class(s->h->c_v_main_e, "black");
    gtk_style_context_add_class(s->h->c_v_bt_e, "black");
    gtk_style_context_add_class(s->h->c_v_bt_like, "black");
    gtk_style_context_add_class(s->h->c_v_bt_aut, "black");
    gtk_style_context_add_class(s->h->c_v_bt_info, "black");
    gtk_style_context_add_class(s->h->c_v_bt_s1, "black");
    gtk_style_context_add_class(s->h->c_v_bt_s2, "black");
    gtk_style_context_add_class(s->h->c_v_bt_s3, "black");
    gtk_style_context_add_class(s->h->c_v_bt_s4, "black");
    gtk_style_context_add_class(s->h->c_v_bt_s5, "black");
    gtk_style_context_add_class(s->h->c_v_bt_s6, "black");
    gtk_style_context_add_class(s->h->c_v_t_btn_b, "black");
    gtk_style_context_add_class(s->h->c_v_t_btn_w, "black");
}

void mx_set_white(t_s *s) {
    mx_remove_class_black(s);
    mx_add_class_white(s);
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "ui");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "tema", "white");
    cJSON_AddStringToObject(send, "lang", s->h->lang);
    char *res = cJSON_Print(send);

    tls_write(s->c->tls, res, strlen(res) + 1);
}


void mx_set_black(t_s *s) {
    mx_remove_class_white(s);
    mx_add_class_black(s);
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "ui");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "tema", "black");
    cJSON_AddStringToObject(send, "lang", s->h->lang);
    char *res = cJSON_Print(send);

    tls_write(s->c->tls, res, strlen(res) + 1);
}

void mx_set_standart_style(t_s *s) {
    gtk_style_context_add_class(s->h->c_v_t_btn_b, "black_theme");
    gtk_style_context_add_class(s->h->c_v_t_btn_w, "white_theme");
    gtk_widget_set_name(s->h->v_main_e, "main_entry");
}

