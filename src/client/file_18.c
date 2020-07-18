#include "client.h"



char *mx_get_new_body(char *str, t_s *s) {
    char *new_str = strdup(str);

    if (mx_is_have_cmd(new_str)) {
        new_str = mx_get_new_body_str(new_str);
    }
    if (s->h->is_output_matyki) {
        new_str = mx_get_without_mats(new_str);
    }
    return new_str;
}



void mx_create_row(t_info *inf, t_s *s) {   
    t_row *row = malloc(sizeof(t_row));

    mx_init_row(row, inf, s);
    if (mx_check_on_cmd(inf->body)) {
        mx_print_cmd(row, inf);
        row->is_sticker = 0;
    }
    else if (!mx_check_on_cmd(inf->body)) {
        row->is_sticker = 1;
        char *new_body = mx_get_new_body(inf->body, s);

        row->v_body = gtk_label_new(new_body);
    }
    mx_end_initing(row, inf, s);
    g_idle_add ((int (*)(void *))mx_show_widget, s->h->v_window);
}

void mx_add_class_orang(t_s *s) {
    gtk_style_context_add_class(s->h->c_v_l_btn_ru, "orang");
    gtk_style_context_add_class(s->h->c_v_l_btn_en, "orang");
    gtk_style_context_add_class(s->h->c_v_l_btn_rm, "orang");
    gtk_style_context_add_class(s->h->c_v_scroll, "orang");
    gtk_style_context_add_class(s->h->c_v_main_e, "orang");
    gtk_style_context_add_class(s->h->c_v_bt_e, "orang");
    gtk_style_context_add_class(s->h->c_v_bt_like, "orang");
    gtk_style_context_add_class(s->h->c_v_bt_aut, "orang");
    gtk_style_context_add_class(s->h->c_v_bt_info, "orang");
    gtk_style_context_add_class(s->h->c_v_bt_s1, "orang");
    gtk_style_context_add_class(s->h->c_v_bt_s2, "orang");
    gtk_style_context_add_class(s->h->c_v_bt_s3, "orang");
    gtk_style_context_add_class(s->h->c_v_bt_s4, "orang");
    gtk_style_context_add_class(s->h->c_v_bt_s5, "orang");
    gtk_style_context_add_class(s->h->c_v_bt_s6, "orang");
    gtk_style_context_add_class(s->h->c_v_t_btn_b, "orang");
    gtk_style_context_add_class(s->h->c_v_t_btn_w, "orang");
}



gboolean mx_set_standart_c (t_s *s) {
    mx_set_styles(s);
    return G_SOURCE_REMOVE;
}

void mx_create_msg(t_s *s, cJSON *msg) {
    t_info *inf = malloc(sizeof(t_info));
    
    inf->author = cJSON_GetObjectItemCaseSensitive(msg, "login")->valuestring;
    inf->body = cJSON_GetObjectItemCaseSensitive(msg, "msg")->valuestring;
    inf->timebuf = cJSON_GetObjectItemCaseSensitive(msg, "time")->valuestring;
    inf->id = cJSON_GetObjectItemCaseSensitive(msg, "id")->valueint;
    int sound = cJSON_GetObjectItemCaseSensitive(msg, "sound")->valueint;
    
    if (sound && s->h->is_output_sound)
        write(1,"\a",1);
    if (sound && s->h->is_output_visual) {
        mx_remove_class_white(s);
        mx_remove_class_black(s);
        mx_add_class_orang(s);
        g_timeout_add(3000, (GSourceFunc)mx_set_standart_c, s);
    }
    mx_create_row(inf, s);
}

