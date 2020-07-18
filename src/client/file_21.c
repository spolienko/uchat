#include "client.h"



void mx_can_deleting_set(t_s *s) {
    s->h->can_do_msg = 1;
}

void *mx_watcher_thread(void *ss) {
    t_s *s = (t_s *)ss;

    s->h->can_do_msg = 1;
    g_timeout_add(3000, (GSourceFunc)mx_can_deleting_set, s);
    while (true) {
        bzero(s->c->bufs, 1000);
        poll(s->c->pfd, 2, -1);
        if (s->c->pfd[1].revents & POLLIN) {
            if ((s->c->rc = tls_read(s->c->tls, s->c->bufs, 1000)) <= 0) 
                break;
            cJSON *msg = cJSON_Parse(s->c->bufs);
            
            mx_check_mesage_from_serv(s, msg);
        }
    }
    return (void *)ss;
}


void mx_create_eng(t_s *s) {
    s->h->v_l_btn_ru = gtk_button_new_with_label("RUS");
    s->h->v_l_btn_en = gtk_button_new_with_label("ENG");
    s->h->v_l_btn_rm = gtk_button_new_with_label("Delete");
    s->h->v_bt_e = gtk_button_new_with_label("Send");
    s->h->v_bt_inf = gtk_button_new_with_label("Info");
    s->h->v_bt_lik = gtk_button_new_with_label("Love");
    s->h->v_bt_aut = gtk_button_new_with_label("Beauty");
    s->h->v_bt_s1 = gtk_button_new_with_label("Ok");
    s->h->v_bt_s2 = gtk_button_new_with_label("Sadness");
    s->h->v_bt_s3 = gtk_button_new_with_label("Danger");
    s->h->v_bt_s4 = gtk_button_new_with_label("Sad cat");
    s->h->v_bt_s5 = gtk_button_new_with_label("Question?");
    s->h->v_bt_s6 = gtk_button_new_with_label("Hello");
}

void mx_create_rus(t_s *s) {
    s->h->v_l_btn_ru = gtk_button_new_with_label("РУС");
    s->h->v_l_btn_en = gtk_button_new_with_label("АНГ");
    s->h->v_l_btn_rm = gtk_button_new_with_label("Удалить");
    s->h->v_bt_e = gtk_button_new_with_label("Отправить");
    s->h->v_bt_inf = gtk_button_new_with_label("Информация");
    s->h->v_bt_lik = gtk_button_new_with_label("Любовь");
    s->h->v_bt_aut = gtk_button_new_with_label("Красота");
    s->h->v_bt_s1 = gtk_button_new_with_label("Хорошо");
    s->h->v_bt_s2 = gtk_button_new_with_label("Грусть");
    s->h->v_bt_s3 = gtk_button_new_with_label("Опасность");
    s->h->v_bt_s4 = gtk_button_new_with_label("Грустный Кот");
    s->h->v_bt_s5 = gtk_button_new_with_label("Вопрос?");
    s->h->v_bt_s6 = gtk_button_new_with_label("Привет");
}

void mx_create_content(t_s *s) {
    if (!strcmp(s->h->lang, "eng")) {
        mx_create_eng(s);
        return;
    }
    if (!strcmp(s->h->lang, "rus")) {
        mx_create_rus(s);
        return;
    }
    mx_create_eng(s);
}

