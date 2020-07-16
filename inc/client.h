#ifndef CLIENT_H
#define CLIENT_H

#include "uchat.h"
#include <gtk/gtk.h>


typedef struct s_clt {
    struct addrinfo h;
    struct addrinfo *p_ad;
    int sock;
    int err;
    int enable;
    struct tls *tls;
    struct tls_config *cnf;
    char address_buffer[100];
    char service_buffer[100];
    char bufs[1000];
    char bufc[1000]; 
    struct pollfd pfd[2];
    ssize_t rc;
}              t_clt;

typedef struct s_lgn {
    int login_in;
    char *login;
    char **argv;
    char *pass;
    char *lang;
    char *theme;
    GtkWidget *win;
    GtkWidget *main_l;
    GtkWidget *user_lbl;
    GtkWidget *pass_lbl;
    GtkWidget *user_ety;
    GtkWidget *pass_ety;
    GtkWidget *e_lbl;
    GtkWidget *ok_btn;
    GtkWidget *vbox;
    GtkWidget *m_lbl_b;
    GtkWidget *u_box;
    GtkWidget *p_box;
    GtkWidget *e_box;
    GtkWidget *ok_btn_b;
    GtkStyleContext *c_window;
    GtkStyleContext *c_main_label;
    GtkStyleContext *c_user_lbl;
    GtkStyleContext *c_pass_lbl;
    GtkStyleContext *c_user_ety;
    GtkStyleContext *c_pass_ety;
    GtkStyleContext *c_error_label;
    GtkStyleContext *c_ok_button;
    GtkCssProvider *SP;
}              t_lgn;

typedef struct s_ct {
    char *login;
    char *lang;
    char *theme;
    char window_title[100];
    char *drop_acc;
    int v_n;
    int d_id;
    int cant_d_id;
    int e_id;
    char *edit_txt;
    int was_connect;
    int can_do_msg;
    int is_output_matyki;
    int is_output_sound;
    int is_output_visual;
    int is_drop_all_messages;

    GtkWidget *v_window;
    GtkWidget *v_main_grid;
    GtkWidget *v_l_btn_ru;
    GtkWidget *v_l_btn_en;
    GtkWidget *v_t_btn_b;
    GtkWidget *v_t_btn_w;
    GtkWidget *v_l_btn_rm;
    GtkWidget *v_scroll;
    GtkWidget *v_main_e;
    GtkWidget *v_bt_e;
    GtkWidget *v_bt_lik;
    GtkWidget *v_bt_aut;
    GtkWidget *v_bt_inf;
    GtkWidget *v_bt_s1;
    GtkWidget *v_bt_s2;
    GtkWidget *v_bt_s3;
    GtkWidget *v_bt_s4;
    GtkWidget *v_bt_s5;
    GtkWidget *v_bt_s6;
    GtkWidget *vbox;
    GtkWidget *T_b;
    GtkWidget *scr_box;
    GtkWidget *ent_box;
    GtkWidget *btns_b;
    pthread_t watcher;
    GtkStyleContext *c_v_window;
    GtkStyleContext *c_v_main_grid;
    GtkStyleContext *c_v_l_btn_ru;
    GtkStyleContext *c_v_l_btn_en;
    GtkStyleContext *c_v_t_btn_b;
    GtkStyleContext *c_v_t_btn_w;
    GtkStyleContext *c_v_l_btn_rm;
    GtkStyleContext *c_v_scroll;
    GtkStyleContext *c_v_main_e;
    GtkStyleContext *c_v_bt_e;
    GtkStyleContext *c_v_bt_like;
    GtkStyleContext *c_v_bt_aut;
    GtkStyleContext *c_v_bt_info;
    GtkStyleContext *c_v_bt_s1;
    GtkStyleContext *c_v_bt_s2;
    GtkStyleContext *c_v_bt_s3;
    GtkStyleContext *c_v_bt_s4;
    GtkStyleContext *c_v_bt_s5;
    GtkStyleContext *c_v_bt_s6;
    GtkCssProvider *cssProv;
    GtkWidget *v_listbox;
    GtkWidget *c_v_listbox;
}              t_ct;

typedef struct s_s {
    t_clt *c;
    t_lgn *l;
    t_ct *h;
}              t_s;

typedef struct s_inf_row {
    GtkWidget *v_row;
    GtkWidget *v_vrow_box;
    GtkWidget *v_hrow;
    GtkWidget *v_body;
    GtkStyleContext *c_v_body;
}              t_inf_row;

typedef struct s_info {
    char *author;
    char *body;
    char *timebuf;
    int id;
}              t_info;


typedef struct s_row {
    int is_sticker;
    GtkWidget *v_row;
    GtkWidget *v_vrow_box;
    GtkWidget *v_hrow;
    GtkWidget *v_taa_box;
    GtkWidget *v_author;
    GtkWidget *v_time;
    GtkWidget *v_body;
    GtkWidget *v_bt_del;
    GtkWidget *v_bt_ed;
    GtkStyleContext *c_v_author;
    GtkStyleContext *c_v_time;
    GtkStyleContext *c_v_body;
    GtkStyleContext *c_v_bt_del;
    GtkStyleContext *c_v_bt_ed;
}              t_row;


typedef struct s_for_click {
    t_row *row;
    t_info *inf;
    t_s *s;
}              t_for_click;

#endif
