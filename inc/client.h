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



void mx_set_styles(t_s *s);
void mx_remove_class_white(t_s *s);
void mx_remove_class_black(t_s *s);
int mx_exit_chat(t_s *s);
void mx_report_1(time_t t, const char *ocsp_url, t_s *s, char *host);
void mx_report_2(time_t t, t_s *s);
void mx_report_tls_client(t_s *s, char *host);
void mx_first_serv_init(t_s *s);
int mx_second_serv_init(t_s *s, char **argv);
int mx_third_serv_init(t_s *s);
int mx_init_server(t_s *s, char **argv);
char *mx_help_str_eng();
char *mx_help_str_rus();
char *mx_help_str(t_s *s);
int mx_is_digit_for_editing(char *m, int i[2]);
int mx_is_have_editing(char *m);
int mx_get_editing_id(char *m);
char *mx_strneww(int size);
char *mx_get_new_body_e(char *m);
char *mx_edit_creating(char *m, t_s *s);
int mx_is_have_drop(char *m);
char *mx_get_user_drop(char *m);
char *mx_drop_creating(char *m, t_s *s);
int mx_is_have_change_pass(char *m);
char *mx_get_new_pass(char *m);
char *mx_change_pass_creating(char *m, t_s *s);
int mx_is_have_matyki(char *m, t_s *s);
int mx_is_have_sound(char *m, t_s *s);
int mx_is_have_visual(char *m, t_s *s);
int mx_is_have_clean_history(char *m);
char *mx_clean_history( t_s *s);
char *mx_parsing_normal_mess(char *m, t_s *s);
int mx_is_have_privat_message(char *m);
char *mx_get_user_for_privat(char *m);
char *mx_create_privat_message(char *m, t_s *s);
char *mx_parsing_mes(char *m, t_s *s);
void mx_do_s(GtkWidget *widget, t_s *s);
void mx_drop_sesion(t_s *s);
void mx_set_class_for_help(t_inf_row *inf);
void init_help(t_inf_row *inf, t_s *s);
int mx_show_widget(GtkWidget *widget);
void mx_inf(GtkWidget *widget, t_s *s);
void mx_closeApp(GtkWidget *window, t_s *s);
void mx_closeApp2(GtkWidget *window, t_s *s);
char *mx_get_cmd(char *str);
int mx_check_on_cmd(char *str);
char *mx_what_return(int gg);
void mx_sen0(GtkWidget *widget, t_s *s);
void mx_sen1(GtkWidget *widget, t_s *s);
void mx_sen2(GtkWidget *widget, t_s *s);
void mx_sen3(GtkWidget *widget, t_s *s);
void mx_sen4(GtkWidget *widget, t_s *s);
void mx_sen5(GtkWidget *widget, t_s *s);
void mx_sen6(GtkWidget *widget, t_s *s);
void mx_sen7(GtkWidget *widget, t_s *s);
void mx_init_row(t_row *row, t_info *inf, t_s *s);
void mx_delete(GtkWidget *widget, t_for_click *c);
void mx_set_class_for_X(t_row *row, t_info *inf, t_s *s);
gboolean mx_check_editing(t_for_click *c);
void mx_print_X(t_row *row, t_info *inf, t_s *s);
void mx_edit(GtkWidget *widget, t_for_click *c);
void mx_print_E(t_row *row, t_info *inf, t_s *s);
void mx_set_bold_line(t_row *row);
void mx_set_italic_line(t_row *row);
void mx_set_red_line(t_row *row);
void mx_set_lime_line(t_row *row);
void mx_set_orange_line(t_row *row);
void mx_set_h1_line(t_row *row);
void mx_set_h2_line(t_row *row);
void mx_set_styles_for_mess(t_row *row, char *str, t_info *inf);
char *mx_parsing_cmd(char *str);
void mx_set_class_for_elem(t_row *row, t_info *inf);
void mx_end_initing(t_row *row, t_info *inf, t_s *s);
void mx_do_print_img(t_row *row, t_info *inf, GdkPixbuf *px);
void mx_print_img(t_row *row, t_info *inf);
char *mx_love();
void mx_print_text(t_row *row, t_info *inf);
void mx_print_cmd(t_row *row, t_info *inf);
char *mx_get_new_body_str(char *new_str);
int mx_is_have_cmd(char *str);
int mx_arr_size(char **arr);
char *mx_strncat(char *restrict s1, const char *restrict s2, size_t n);
char *mx_replace_sub(const char *str, const char *sub,
                     const char *replace);
char *mx_get_without_mats(char *new_str);
char *mx_get_new_body(char *str, t_s *s);
void mx_create_row(t_info *inf, t_s *s);
void mx_add_class_orang(t_s *s);
gboolean mx_set_standart_c (t_s *s);
void mx_create_msg(t_s *s, cJSON *msg);
void mx_delete_msg(t_s *s, cJSON *msg);
void mx_edit_mess(t_s *s, cJSON *msg);
void mx_init_connect_msg(t_s *s, cJSON *msg);
void mx_drop_acc(GtkWidget *widget, t_s *s);
void mx_droping_account(t_s *s, cJSON *msg);
gboolean mx_set_cant_delete_all_mes(t_s *s);
void mx_drop_all_messages(t_s *s);
char *mx_create_privat_message_body(cJSON *msg);
void mx_create_privat_mes(t_s *s, cJSON *msg);
void mx_check_mesage_from_serv(t_s *s, cJSON *msg);
void mx_can_deleting_set(t_s *s);
void mx_create_eng(t_s *s);
void mx_create_rus(t_s *s);
void mx_create_content(t_s *s);
void mx_1_chat_init(t_s *s);
void mx_2_chat_init(t_s *s);
void mx_3_chat_init(t_s *s);
void mx_remove_class_black(t_s *s);
void mx_remove_class_white(t_s *s);
void mx_add_class_white(t_s *s);
void mx_add_class_black(t_s *s);
void mx_set_white(t_s *s);
void mx_set_black(t_s *s);
void mx_set_standart_style(t_s *s);
void mx_set_styles(t_s *s);
void mx_4_chat_init(t_s *s);
void mx_set_b(GtkWidget *widget, t_s *s);
void mx_set_w(GtkWidget *widget, t_s *s);
void mx_set_engl(t_s *s);
void mx_set_russ(t_s *s);
void mx_set_en(GtkWidget *widget, t_s *s);
void mx_set_ru(GtkWidget *widget, t_s *s);
void mx_5_chat_init(t_s *s);
void mx_6_chat_init(t_s *s);
void mx_7_chat_init(t_s *s);
void mx_send_conection(t_s *s);
void mx_init_chatt(t_s *s);
int mx_check_on_input(GtkWidget *widget, t_s *s);
void mx_work_in_while(t_s *s);
void mx_init_while_login(t_s *s);
void mx_do_logining(GtkWidget *widget, t_s *s);
gboolean mx_check_logining(t_s *s);
void mx_init_logining_1(t_s *s);
void mx_init_logining_2(t_s *s);
void mx_init_logining_3(t_s *s);
void mx_init_logining_4(t_s *s);


#endif
