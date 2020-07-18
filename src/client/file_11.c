#include "client.h"

void mx_sen3(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = mx_what_return(3);
        char *m = malloc(strlen(message) + 1);    

        strcpy(m, message);
        cJSON *send = cJSON_CreateObject();
        char *res;

        cJSON_AddStringToObject(send, "kind", "msg");
        cJSON_AddStringToObject(send, "login", s->h->login);
        cJSON_AddStringToObject(send, "msg", m);
        res = cJSON_Print(send);
        tls_write(s->c->tls, res, strlen(res) + 1);
        gtk_entry_set_text(GTK_ENTRY(s->h->v_main_e), "");
    }
    (void)widget;
}


void mx_sen4(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = mx_what_return(4);
        char *m = malloc(strlen(message) + 1);    

        strcpy(m, message);
        cJSON *send = cJSON_CreateObject();
        char *res;

        cJSON_AddStringToObject(send, "kind", "msg");
        cJSON_AddStringToObject(send, "login", s->h->login);
        cJSON_AddStringToObject(send, "msg", m);
        res = cJSON_Print(send);
        tls_write(s->c->tls, res, strlen(res) + 1);
        gtk_entry_set_text(GTK_ENTRY(s->h->v_main_e), "");
    }
    (void)widget;
}

void mx_sen5(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = mx_what_return(5);
        char *m = malloc(strlen(message) + 1);    

        strcpy(m, message);
        cJSON *send = cJSON_CreateObject();
        char *res;

        cJSON_AddStringToObject(send, "kind", "msg");
        cJSON_AddStringToObject(send, "login", s->h->login);
        cJSON_AddStringToObject(send, "msg", m);
        res = cJSON_Print(send);
        tls_write(s->c->tls, res, strlen(res) + 1);
        gtk_entry_set_text(GTK_ENTRY(s->h->v_main_e), "");
    }
    (void)widget;
}

void mx_sen6(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = mx_what_return(6);
        char *m = malloc(strlen(message) + 1);  

        strcpy(m, message);
        cJSON *send = cJSON_CreateObject();
        char *res;

        cJSON_AddStringToObject(send, "kind", "msg");
        cJSON_AddStringToObject(send, "login", s->h->login);
        cJSON_AddStringToObject(send, "msg", m);
        res = cJSON_Print(send);
        tls_write(s->c->tls, res, strlen(res) + 1);
        gtk_entry_set_text(GTK_ENTRY(s->h->v_main_e), "");
    }
    (void)widget;
}

void mx_sen7(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = mx_what_return(7);
        char *m = malloc(strlen(message) + 1);   

        strcpy(m, message);
        cJSON *send = cJSON_CreateObject();
        char *res;

        cJSON_AddStringToObject(send, "kind", "msg");
        cJSON_AddStringToObject(send, "login", s->h->login);
        cJSON_AddStringToObject(send, "msg", m);
        res = cJSON_Print(send);
        tls_write(s->c->tls, res, strlen(res) + 1);
        gtk_entry_set_text(GTK_ENTRY(s->h->v_main_e), "");
    }
    (void)widget;
}
