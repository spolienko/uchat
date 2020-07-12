#include "client.h"
#include "cJSON.h"




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
    int v_n;
    int delete_id;
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
    t_clt *c;//client
    t_lgn *l;//logining
    t_ct *h;//chat
}              t_s;

typedef struct s_inf_row{
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

int mx_exit_chat(t_s *s) {
    tls_close(s->c->tls);
    tls_free(s->c->tls);
    tls_config_free(s->c->cnf);
    printf("Closing socket...\n");
    close(s->c->sock);
    printf("exit client\n");
    return 0;
}

char *help_str_eng() {
    char *sss = "Rules: max str len 100 chars\n"
        "Comands write only: |cmd|"
        "Editing: |123| - font-size, |rol| - color, |inb| - fonts\n"
        "Stickers: |++++|,\n"
        "Special cmds: |k[id]|";
    return sss;
}

char *help_str_rus() {
    char *sss = "Ychi English\n"
        "Ychi EnglishComands write only: |cmd|\n"
        "Ychi EnglishEditing: |123| - font-size, |rol| - color, |inb| - fonts\n"
        "Ychi EnglishStickers: |++++|,\n"
        "Ychi EnglishSpecial cmds: |k[id]|";
    return sss;
}

char *help_str(t_s *s){
    if (!strcmp(s->h->lang, "eng"))
        return help_str_eng();
    if (!strcmp(s->h->lang, "rus"))
        return help_str_rus();
    return help_str_eng();        
}

bool mx_isspace(char c) {
    return c == 32 || (c > 8 && c < 14);
}

char *trim(char *s) {
    unsigned long i = 0;
    unsigned long j;

    while ((s[i] == ' ') || (s[i] == '\t'))
        i++;
    if (i > 0) {
        for (j = 0; j < strlen(s); j++)
              s[j]=s[j+i];
        s[j]='\0';
    }
    i = strlen(s)-1;
    while (mx_isspace(s[i]))
        i--;
    if (i < (strlen(s) - 1))
        s[i + 1] = '\0';
    return s;
}

void do_s(GtkWidget *widget, t_s *s) {
    char *message = (char *)gtk_entry_get_text(GTK_ENTRY(s->h->v_main_e));
    if(!message || !*message)
        return;
    char *m = malloc(strlen(message) + 1);    
    strcpy(m, trim(message));
    cJSON *send = cJSON_CreateObject();
    char *res;
    cJSON_AddStringToObject(send, "kind", "msg");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "msg", m);
    res = cJSON_Print(send);

    // if (strlen(m) < 100 && strlen(m) > 0)
    // // message_send(m);
    printf("%s\n", res);
    // else {
    //     printf("to manywords\n");
    // }
    tls_write(s->c->tls, res, strlen(res) + 1);

    gtk_entry_set_text(GTK_ENTRY(s->h->v_main_e), "");

    (void)widget;
}

void set_class_for_help(t_inf_row *inf) {
    inf->c_v_body = gtk_widget_get_style_context(inf->v_body);
    gtk_style_context_add_class(inf->c_v_body, "orange");
    gtk_style_context_add_class(inf->c_v_body, "h2");
    gtk_style_context_add_class(inf->c_v_body, "normal");
    gtk_style_context_add_class(inf->c_v_body, "pading_left_100");
}

void init_help(t_inf_row *inf, t_s *s) {
    char *str = help_str(s);

    inf->v_row = gtk_list_box_row_new();
    gtk_list_box_insert((GtkListBox *)s->h->v_listbox, inf->v_row, s->h->v_n);
    s->h->v_n++;
    inf->v_hrow = gtk_box_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(inf->v_row), inf->v_hrow);
    inf->v_body = gtk_label_new(str);
    gtk_box_pack_start(GTK_BOX(inf->v_hrow), inf->v_body, FALSE, FALSE, 0);
    gtk_widget_set_size_request(inf->v_body, 250, 10);
    gtk_label_set_xalign((GtkLabel *)inf->v_body, 0.1);
    set_class_for_help(inf);
}

void inf(GtkWidget *widget, t_s *s) {
    (void)widget;
    t_inf_row *inf = malloc(sizeof(t_inf_row));

    init_help(inf, s);
    gtk_widget_show_all(s->h->v_window);
}


void closeApp(GtkWidget *window, t_s *s)
{   
    (void)window;
    mx_exit_chat(s);
    printf("Destroy\n");
    gtk_main_quit();
}

char *get_cmd(char *str) {
    int arr[300];
    int arrr[2] = {0, 0};

    arr[0] = 0;
    arr[1] = 0;
    while (str[arrr[1]] != '\0') {
        if (str[arrr[1]] == '|') {
            arr[arrr[0]] = arrr[1];
            arrr[0]++;
        }
        arrr[1]++;
    }
    return strndup(str + arr[0], arr[1] + 1);
}

int check_on_cmd(char *str) {
    char *strr = get_cmd(str);
    if (!strcmp(strr, "|love|"))
        return 1;
    if (!strcmp(strr, "|aut|"))
        return 2;
    if (!strcmp(strr, "|++++|"))
        return 3;
    if (!strcmp(strr, "|sadness|"))
        return 4;
    if (!strcmp(strr, "|danger|"))
        return 5;
    if (!strcmp(strr, "|sad_cat|"))
        return 6;
    if (!strcmp(strr, "|????|"))
        return 7;
    if (!strcmp(strr, "|hello|"))
        return 8;
    return 0;
}

char *what_return(int gg) {
    if (gg == 0)
        return "|love|";
    if (gg == 1)
        return "|aut|";
    if (gg == 2)
        return "|++++|";
    if (gg == 3)
        return "|sadness|";
    if (gg == 4)
        return "|danger|";
    if (gg == 5)
        return "|sad_cat|";
    if (gg == 6)
        return "|????|";
    if (gg == 7)
        return "|hello|";
    return "err";
} 

void sen(GtkWidget *widget, int gg){
    char *message = what_return(gg);
    char *m = malloc(strlen(message) + 1);

    strcpy(m, message);
    // message_send(m);
    (void)widget;
}

typedef struct s_row {
    GtkWidget *v_row;
    GtkWidget *v_vrow_box;
    GtkWidget *v_hrow;
    GtkWidget *v_taa_box;
    GtkWidget *v_author;
    GtkWidget *v_time;
    GtkWidget *v_body;
    GtkWidget *v_bt_del;
    GtkStyleContext *c_v_author;
    GtkStyleContext *c_v_time;
    GtkStyleContext *c_v_body;
    GtkStyleContext *c_v_bt_del;
}              t_row;

void init_row(t_row *row, t_info *inf, t_s *s) {
    row->v_row = gtk_list_box_row_new();
    gtk_list_box_insert((GtkListBox *)s->h->v_listbox, row->v_row, s->h->v_n);
    s->h->v_n++;
    row->v_hrow = gtk_box_new(FALSE, 0);
    row->v_taa_box = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(row->v_row), row->v_hrow);
    row->v_author = gtk_label_new(inf->author);
    gtk_box_pack_start(GTK_BOX(row->v_taa_box), row->v_author,
                       FALSE, FALSE, 0);
    gtk_widget_set_size_request(row->v_author,250,30);
    row->v_time = gtk_label_new(inf->timebuf);
    gtk_box_pack_start(GTK_BOX(row->v_taa_box), row->v_time, FALSE,
                               FALSE, 0);
    gtk_widget_set_size_request(row->v_time,250,30);
    gtk_container_add(GTK_CONTAINER(row->v_hrow), row->v_taa_box);
}

//X
typedef struct s_for_click {
    t_row *row;
    t_info *inf;
    t_s *s;
}              t_for_click;

void delete (GtkWidget *widget, t_for_click *c) {
    // gtk_container_remove ((GtkContainer *)c->s->h->v_listbox, c->row->v_row);
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "delete");
    cJSON_AddStringToObject(send, "login", c->s->h->login);
    cJSON_AddNumberToObject(send, "id", c->inf->id);
    char *res = cJSON_Print(send);
    printf("%s\n", res);
    tls_write(c->s->c->tls, res, strlen(res) + 1);
    (void)widget;
}

void set_class_for_X(t_row *row, t_info *inf, t_s *s){
    row->c_v_bt_del = gtk_widget_get_style_context(row->v_bt_del);
    gtk_style_context_add_class(row->c_v_bt_del, "X");
    (void)inf;
    (void)s;
}

gboolean check_deleting(t_for_click *c) {
    printf("%d\t%d \n", c->inf->id, c->s->h->delete_id);
    if (c->s->h->delete_id == c->inf->id){
        gtk_container_remove((GtkContainer *)c->s->h->v_listbox, c->row->v_row);
        // printf("%d\n", c->inf->id);
        c->s->h->delete_id = -2;
        return G_SOURCE_REMOVE;
    }
    return G_SOURCE_CONTINUE;
}

void print_X(t_row *row, t_info *inf, t_s *s) {
    t_for_click *c = malloc(sizeof(t_for_click));
    c->row = row;
    c->inf = inf;
    c->s = s;
    if(!strcmp(inf->author, s->h->login)) {

        row->v_bt_del = gtk_button_new_with_label("X");
        gtk_widget_set_name(row->v_bt_del, "X");
        gtk_box_pack_start(GTK_BOX(row->v_hrow), 
        row->v_bt_del, FALSE, FALSE, 0);
        set_class_for_X(row, inf, s);
        g_signal_connect(G_OBJECT(row->v_bt_del), "clicked", G_CALLBACK(delete), c);
    }
    
    g_timeout_add(500, (GSourceFunc)check_deleting, c);
}

void end_initing(t_row *row, t_info *inf, t_s *s) {
    (void)inf,(void) s;
    gtk_box_pack_start(GTK_BOX(row->v_hrow), row->v_body, FALSE, FALSE, 0);
    gtk_widget_set_size_request(row->v_body,1300,30);
    // if(!check_on_cmd(inf->body))
    //     gtk_label_set_xalign((GtkLabel *)row->v_body, 0.04);
    gtk_widget_set_size_request(row->v_body,80,30);
    print_X(row, inf, s);
    // set_class_for_elem(row, inf, chat);
}

void do_print_img(t_row *row, t_info *inf, GdkPixbuf *pixbuf){
    if (check_on_cmd(inf->body) == 7)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("src/client/img/?.png",
            340, 340, TRUE, NULL);
    if (check_on_cmd(inf->body) == 8)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("src/client/img/hello.png",
            340, 340, TRUE, NULL);
    if (check_on_cmd(inf->body) == 2)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("src/client/img/aut.jpg",
            250, 250, TRUE, NULL);
    row->v_body = gtk_image_new_from_pixbuf(pixbuf);
}

void print_img(t_row *row, t_info *inf) {
    GdkPixbuf *pixbuf;

    if (check_on_cmd(inf->body) == 3)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("src/client/img/+.png", 
            340, 340, TRUE, NULL);
    if (check_on_cmd(inf->body) == 4)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("src/client/img/sadness.png", 
            340, 340, TRUE, NULL);
    if (check_on_cmd(inf->body) == 5)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("src/client/img/danger.png",
            270, 270, TRUE, NULL);
    if (check_on_cmd(inf->body) == 6)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("src/client/img/sad_cat.png",
            390, 390, TRUE, NULL);
    do_print_img(row, inf, pixbuf);
}


char *love(){
    char *message = "___$$$$$$$$______$$$$$$$$$\n"
        "_$$$$$$$$$$$$__$$$$$$$__$$$$\n"
        "$$$$$$$$$$$$$$$$$$$$$$$$__$$$\n"
        "$$$$$$$$$$$$$$$$$$$$$$$$__$$$\n"
        "$$$$$$$$$$$$$$$$$$$$$$$$__$$$\n"
        "_$$$$$$$$$$$$$$$$$$$$$$__$$$\n"
        "___$$$$$$$$$$$$$$$$$$$$$$$\n"
        "______$$$$$$$$$$$$$$$$$\n"
        "________$$$$$$$$$$$$$\n"
        "___________$$$$$$$\n"
        "_____________$$$\n"
        "______________$\n";

    return message;
}

void print_text(t_row *row, t_info *inf) {
    if (check_on_cmd(inf->body) == 1)
        row->v_body = gtk_label_new(love());
}

void print_cmd(t_row *row, t_info *inf) {
    if (check_on_cmd(inf->body) > 1)
        print_img(row, inf);
    if (check_on_cmd(inf->body) == 1)
        print_text(row, inf);
}

void create_row(t_info *inf, t_s *s) {   
    t_row *row = malloc(sizeof(t_row));

    init_row(row, inf, s);
    if (check_on_cmd(inf->body)) {
        print_cmd(row, inf);
    }
    else if (!check_on_cmd(inf->body)) {
        // char *new_body = get_new_body(inf->body);
        row->v_body = gtk_label_new(inf->body);
    }
    end_initing(row, inf, s);
    gtk_widget_show_all(s->h->v_window);
}

void create_msg(t_s *s, cJSON *msg) {
    t_info *inf = malloc(sizeof(t_info));
    
    inf->author = cJSON_GetObjectItemCaseSensitive(msg, "login")->valuestring;
    inf->body = cJSON_GetObjectItemCaseSensitive(msg, "msg")->valuestring;
    inf->timebuf = cJSON_GetObjectItemCaseSensitive(msg, "time")->valuestring;
    inf->id = cJSON_GetObjectItemCaseSensitive(msg, "id")->valueint;
    create_row(inf, s);
}

void delete_msg(t_s *s, cJSON *msg) {
    s->h->delete_id = cJSON_GetObjectItemCaseSensitive(msg, "id")->valueint;
}

void check_mesage_from_serv(t_s *s, cJSON *msg) {
    char *ch = cJSON_GetObjectItemCaseSensitive(msg, "kind")->valuestring;

    if (!strcmp(ch, "msg"))
        create_msg(s, msg);
    if (!strcmp(ch, "delete"))
        delete_msg(s, msg);
}


void watcher_thread(t_s *s) {
    while (true) {
        bzero(s->c->bufs, 1000);
        poll(s->c->pfd, 2, -1);
        if (s->c->pfd[1].revents & POLLIN) {
            if ((s->c->rc = tls_read(s->c->tls, s->c->bufs, 1000)) <= 0) 
                break;
            printf("Mesage (%lu): %s\n", s->c->rc, s->c->bufs);
            cJSON *msg = cJSON_Parse(s->c->bufs);
            check_mesage_from_serv(s, msg);
        }
    }
}


void create_eng(t_s *s) {
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

void create_rus(t_s *s) {
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

void create_content(t_s *s) {
    if(!strcmp(s->h->lang, "eng")){
        create_eng(s);
        return;
    }
    if(!strcmp(s->h->lang, "rus")) {
        create_rus(s);
        return;
    }
    create_eng(s);
}


void mx_1_chat_init(t_s *s) {
    s->h->login = s->l->login;
    s->h->lang = s->l->lang;
    s->h->v_n = 0;
    s->h->theme = s->l->theme;
    create_content(s);
    s->h->v_scroll = gtk_scrolled_window_new(0,0);
    s->h->v_t_btn_b = gtk_button_new_with_label("   ");
    s->h->v_t_btn_w = gtk_button_new_with_label("   ");
    s->h->vbox = gtk_box_new(TRUE, 0);
    s->h->T_b = gtk_box_new(FALSE, 0);
    s->h->scr_box = gtk_box_new(FALSE, 0);
    s->h->ent_box = gtk_box_new(FALSE, 0);
    s->h->btns_b = gtk_box_new(FALSE, 0);
    s->h->v_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    s->h->cssProv = gtk_css_provider_new();
    s->h->v_listbox = gtk_list_box_new();
    s->h->v_main_e = gtk_entry_new();
}

void mx_2_chat_init(t_s *s) {
    gtk_box_pack_start(GTK_BOX(s->h->T_b), s->h->v_l_btn_ru, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->T_b), s->h->v_l_btn_en, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->T_b), s->h->v_t_btn_b, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->T_b), s->h->v_t_btn_w, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->T_b), s->h->v_l_btn_rm, FALSE, TRUE, 0);
    gtk_widget_set_size_request(s->h->v_l_btn_ru, 400, 50);
    gtk_widget_set_size_request(s->h->v_l_btn_en, 400, 50);
    gtk_widget_set_size_request(s->h->v_t_btn_b, 400, 50);
    gtk_widget_set_size_request(s->h->v_t_btn_w, 400, 50);
    gtk_widget_set_size_request(s->h->v_l_btn_rm, 200, 50);
    gtk_box_pack_start(GTK_BOX(s->h->vbox), s->h->T_b, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->vbox), s->h->scr_box, FALSE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(s->h->v_window), s->h->vbox);
    gtk_window_set_resizable((GtkWindow *)s->h->v_window, FALSE);
    gtk_box_pack_start(GTK_BOX(s->h->scr_box), s->h->v_scroll, TRUE, TRUE, 0);
    gtk_widget_set_size_request(s->h->v_scroll,1800,950);
    gtk_box_pack_start(GTK_BOX(s->h->ent_box), s->h->v_main_e, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->ent_box), s->h->v_bt_e, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->vbox), s->h->ent_box, TRUE, FALSE, 0);
    g_signal_connect(G_OBJECT(s->h->v_bt_e), "clicked", G_CALLBACK(do_s), s);
    gtk_widget_set_size_request(s->h->v_bt_e,200,50);
}

void mx_3_chat_init(t_s *s) {
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_inf, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_lik, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_aut, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_s1, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_s2, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_s3, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_s4, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_s5, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_s6, FALSE, TRUE, 0);
    gtk_widget_set_size_request(s->h->v_bt_inf,200,50);
    gtk_widget_set_size_request(s->h->v_bt_lik,200,50);
    gtk_widget_set_size_request(s->h->v_bt_aut,200,50);
    gtk_widget_set_size_request(s->h->v_bt_s1,200,50);
    gtk_widget_set_size_request(s->h->v_bt_s2,200,50);
    gtk_widget_set_size_request(s->h->v_bt_s3,200,50);
    gtk_widget_set_size_request(s->h->v_bt_s4,200,50);
    gtk_widget_set_size_request(s->h->v_bt_s5,200,50);
    gtk_widget_set_size_request(s->h->v_bt_s6,200,50);
    gtk_box_pack_start(GTK_BOX(s->h->vbox), s->h->btns_b, TRUE, FALSE, 0);
}

void mx_remove_class_black(t_s *s) {
    gtk_style_context_remove_class(s->h->c_v_l_btn_ru, "black");
    gtk_style_context_remove_class(s->h->c_v_l_btn_en, "black");
    gtk_style_context_remove_class(s->h->c_v_l_btn_rm, "black");
    gtk_style_context_remove_class(s->h->c_v_scroll, "black");
    gtk_style_context_remove_class(s->h->c_v_main_e, "black");
    gtk_style_context_remove_class(s->h->c_v_bt_e, "black");
    gtk_style_context_remove_class(s->h->c_v_bt_like, "black");
    gtk_style_context_remove_class(s->h->c_v_bt_aut, "black");
    gtk_style_context_remove_class(s->h->c_v_bt_info, "black");
    gtk_style_context_remove_class(s->h->c_v_bt_s1, "black");
    gtk_style_context_remove_class(s->h->c_v_bt_s2, "black");
    gtk_style_context_remove_class(s->h->c_v_bt_s3, "black");
    gtk_style_context_remove_class(s->h->c_v_bt_s4, "black");
    gtk_style_context_remove_class(s->h->c_v_bt_s5, "black");
    gtk_style_context_remove_class(s->h->c_v_bt_s6, "black");
    gtk_style_context_remove_class(s->h->c_v_t_btn_b, "black");
    gtk_style_context_remove_class(s->h->c_v_t_btn_w, "black");
}

void mx_remove_class_white(t_s *s) {
    gtk_style_context_remove_class(s->h->c_v_l_btn_ru, "white");
    gtk_style_context_remove_class(s->h->c_v_l_btn_en, "white");
    gtk_style_context_remove_class(s->h->c_v_l_btn_rm, "white");
    gtk_style_context_remove_class(s->h->c_v_scroll, "white");
    gtk_style_context_remove_class(s->h->c_v_main_e, "white");
    gtk_style_context_remove_class(s->h->c_v_bt_e, "white");
    gtk_style_context_remove_class(s->h->c_v_bt_like, "white");
    gtk_style_context_remove_class(s->h->c_v_bt_aut, "white");
    gtk_style_context_remove_class(s->h->c_v_bt_info, "white");
    gtk_style_context_remove_class(s->h->c_v_bt_s1, "white");
    gtk_style_context_remove_class(s->h->c_v_bt_s2, "white");
    gtk_style_context_remove_class(s->h->c_v_bt_s3, "white");
    gtk_style_context_remove_class(s->h->c_v_bt_s4, "white");
    gtk_style_context_remove_class(s->h->c_v_bt_s5, "white");
    gtk_style_context_remove_class(s->h->c_v_bt_s6, "white");
    gtk_style_context_remove_class(s->h->c_v_t_btn_b, "white");
    gtk_style_context_remove_class(s->h->c_v_t_btn_w, "white");
}

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

void set_white(t_s *s) {
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


void set_black(t_s *s) {
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

void set_standart_style(t_s *s) {
    gtk_style_context_add_class(s->h->c_v_t_btn_b, "black_theme");
    gtk_style_context_add_class(s->h->c_v_t_btn_w, "white_theme");
    gtk_widget_set_name(s->h->v_main_e, "main_entry");
}


void mx_set_styles(t_s *s) {
    if (!strcmp(s->h->theme, "black")) {
        set_black(s);
        set_standart_style(s);
        return;
    }
    if (!strcmp(s->h->theme, "white")) {
        set_white(s);
        set_standart_style(s);
        return;
    }
    set_black(s);
}

void mx_4_chat_init(t_s *s) {
    s->h->c_v_window = gtk_widget_get_style_context(s->h->v_window);
    s->h->c_v_l_btn_ru = gtk_widget_get_style_context(s->h->v_l_btn_ru);
    s->h->c_v_l_btn_en = gtk_widget_get_style_context(s->h->v_l_btn_en);
    s->h->c_v_l_btn_en = gtk_widget_get_style_context(s->h->v_l_btn_en);
    s->h->c_v_l_btn_rm = gtk_widget_get_style_context(s->h->v_l_btn_rm);
    s->h->c_v_t_btn_b = gtk_widget_get_style_context(s->h->v_t_btn_b);
    s->h->c_v_t_btn_w = gtk_widget_get_style_context(s->h->v_t_btn_w);
    s->h->c_v_scroll = gtk_widget_get_style_context(s->h->v_scroll);
    s->h->c_v_main_e = gtk_widget_get_style_context(s->h->v_main_e);
    s->h->c_v_bt_e = gtk_widget_get_style_context(s->h->v_bt_e);
    s->h->c_v_bt_like = gtk_widget_get_style_context(s->h->v_bt_lik);
    s->h->c_v_bt_aut = gtk_widget_get_style_context(s->h->v_bt_aut);
    s->h->c_v_bt_info = gtk_widget_get_style_context(s->h->v_bt_inf);
    s->h->c_v_bt_s1 = gtk_widget_get_style_context(s->h->v_bt_s1);
    s->h->c_v_bt_s2 = gtk_widget_get_style_context(s->h->v_bt_s2);
    s->h->c_v_bt_s3 = gtk_widget_get_style_context(s->h->v_bt_s3);
    s->h->c_v_bt_s4 = gtk_widget_get_style_context(s->h->v_bt_s4);
    s->h->c_v_bt_s5 = gtk_widget_get_style_context(s->h->v_bt_s5);
    s->h->c_v_bt_s6 = gtk_widget_get_style_context(s->h->v_bt_s6);
    mx_set_styles(s);
}

void set_b(GtkWidget *widget, t_s *s) {
    (void)widget;
    set_black(s);
    
}
void set_w(GtkWidget *widget, t_s *s) {
    (void)widget;
    set_white(s);
}

void set_engl(t_s *s) {
    gtk_button_set_label((GtkButton *)s->h->v_l_btn_ru, "RUS");
    gtk_button_set_label((GtkButton *)s->h->v_l_btn_en, "ENG");
    gtk_button_set_label((GtkButton *)s->h->v_l_btn_rm, "Delete");
    gtk_button_set_label((GtkButton *)s->h->v_bt_e, "Send");
    gtk_button_set_label((GtkButton *)s->h->v_bt_inf, "Info");
    gtk_button_set_label((GtkButton *)s->h->v_bt_lik, "Love");
    gtk_button_set_label((GtkButton *)s->h->v_bt_aut, "Beauty");
    gtk_button_set_label((GtkButton *)s->h->v_bt_s1, "Ok");
    gtk_button_set_label((GtkButton *)s->h->v_bt_s2, "Sadness");
    gtk_button_set_label((GtkButton *)s->h->v_bt_s3, "Danger");
    gtk_button_set_label((GtkButton *)s->h->v_bt_s4, "Sad cat");
    gtk_button_set_label((GtkButton *)s->h->v_bt_s5, "Question?");
    gtk_button_set_label((GtkButton *)s->h->v_bt_s6, "Hello");
    s->h->lang = "eng";
}

void set_russ(t_s *s) {
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

void set_en(GtkWidget *widget, t_s *s) {
    (void)widget;
    set_engl(s);
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "ui");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "tema", s->h->theme);
    cJSON_AddStringToObject(send, "lang", "eng");
    char *res = cJSON_Print(send);

    tls_write(s->c->tls, res, strlen(res) + 1);
}

void set_ru(GtkWidget *widget, t_s *s) {
    (void)widget;
    set_russ(s);
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "ui");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "tema", s->h->theme);
    cJSON_AddStringToObject(send, "lang", "rus");
    char *res = cJSON_Print(send);

    tls_write(s->c->tls, res, strlen(res) + 1);
}

void drop_acc(GtkWidget *widget, t_s *s) {
    (void)widget;
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "drop_acc");
    cJSON_AddStringToObject(send, "login", s->h->login);
    char *res = cJSON_Print(send);

    tls_write(s->c->tls, res, strlen(res) + 1);
    closeApp(s->h->v_window, s);

}

void init_chatt(t_s *s) {
    mx_1_chat_init(s);
    mx_2_chat_init(s);
    mx_3_chat_init(s);
    mx_4_chat_init(s);
    s->h->delete_id = -2;
    
    g_signal_connect(G_OBJECT(s->h->v_l_btn_en), "clicked", G_CALLBACK(set_en), s);
    g_signal_connect(G_OBJECT(s->h->v_l_btn_ru), "clicked", G_CALLBACK(set_ru), s);
    

    
    g_signal_connect(G_OBJECT(s->h->v_t_btn_b), "clicked", G_CALLBACK(set_b), s);
    g_signal_connect(G_OBJECT(s->h->v_t_btn_w), "clicked", G_CALLBACK(set_w), s);
    g_signal_connect(G_OBJECT(s->h->v_l_btn_rm), "clicked", G_CALLBACK(drop_acc), s);


    
    g_signal_connect(G_OBJECT(s->h->v_bt_inf), "clicked", G_CALLBACK(inf), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_lik), "clicked", G_CALLBACK(sen), (gpointer)0);
    g_signal_connect(G_OBJECT(s->h->v_bt_aut), "clicked", G_CALLBACK(sen), (gpointer)1);
    g_signal_connect(G_OBJECT(s->h->v_bt_s1), "clicked", G_CALLBACK(sen), (gpointer)2);
    g_signal_connect(G_OBJECT(s->h->v_bt_s2), "clicked", G_CALLBACK(sen), (gpointer)3);
    g_signal_connect(G_OBJECT(s->h->v_bt_s3), "clicked", G_CALLBACK(sen), (gpointer)4);
    g_signal_connect(G_OBJECT(s->h->v_bt_s4), "clicked", G_CALLBACK(sen), (gpointer)5);
    g_signal_connect(G_OBJECT(s->h->v_bt_s5), "clicked", G_CALLBACK(sen), (gpointer)6);
    g_signal_connect(G_OBJECT(s->h->v_bt_s6), "clicked", G_CALLBACK(sen), (gpointer)7);

    gtk_container_add(GTK_CONTAINER(s->h->v_scroll), s->h->v_listbox);
    g_signal_connect(s->h->v_window,"destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_scrolled_window_set_max_content_width ((GtkScrolledWindow *)s->h->v_scroll, 500);
    gtk_window_set_title(GTK_WINDOW(s->h->v_window), (const gchar *)"uchat");
    gtk_widget_show_all((GtkWidget *)s->h->v_window);

    char *m = mx_strjoin(s->h->login, " conacted");
    cJSON *send = cJSON_CreateObject();
    char *res;
    cJSON_AddStringToObject(send, "kind", "msg");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "msg", m);
    res = cJSON_Print(send);

    // if (strlen(m) < 100 && strlen(m) > 0)
    // // message_send(m);
    // printf("%s\n", res);
    // else {
    //     printf("to manywords\n");
    // }
    tls_write(s->c->tls, res, strlen(res) + 1);

    pthread_t thread_input;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int tc = pthread_create(&thread_input, &attr, (void * _Nullable (* _Nonnull)(void * _Nullable))watcher_thread, s);
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

void do_logining(GtkWidget *widget, t_s *s) {
    if (mx_check_on_input(widget, s))
        return;
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "login");
    cJSON_AddStringToObject(send, "login", s->l->login);
    cJSON_AddStringToObject(send, "pasword", s->l->pass);
    char *res = cJSON_Print(send);

    tls_write(s->c->tls, res, strlen(res) + 1);
    mx_init_while_login(s);
}

gboolean check_logining(t_s *s) {
    if(s->l->login_in) {
        s->l->login_in = 0;
        gtk_widget_hide(s->l->win);
        init_chatt(s);
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
    gtk_widget_show_all(s->l->win);
    // gtk_window_set_position(GTK_WINDOW(s->l->win), GTK_WIN_POS_CENTER_ALWAYS); !!!!!
    gtk_entry_set_visibility(GTK_ENTRY(s->l->pass_ety), FALSE);
    gtk_window_set_resizable (GTK_WINDOW(s->l->win), FALSE);
    gtk_css_provider_load_from_path(s->l->SP, "src/client/theme.css", NULL);
    gtk_style_context_add_provider_for_screen( gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(s->l->SP),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_set_title(GTK_WINDOW(s->l->win), "Uchat");
    g_signal_connect(G_OBJECT(s->l->win), "destroy", G_CALLBACK(closeApp), s);
    s->l->c_window = gtk_widget_get_style_context(s->l->win);
    s->l->c_main_label = gtk_widget_get_style_context(s->l->main_l);
    s->l->c_user_lbl = gtk_widget_get_style_context(s->l->user_lbl);
    s->l->c_pass_lbl = gtk_widget_get_style_context(s->l->pass_lbl);
    s->l->c_user_ety = gtk_widget_get_style_context(s->l->user_ety);
    s->l->c_pass_ety = gtk_widget_get_style_context(s->l->pass_ety);
    s->l->c_error_label = gtk_widget_get_style_context(s->l->e_lbl);
    s->l->c_ok_button = gtk_widget_get_style_context(s->l->ok_btn);
}


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
                     G_CALLBACK(do_logining), s);
    gtk_container_add(GTK_CONTAINER(s->l->win), s->l->vbox);
    g_timeout_add(50, (GSourceFunc)check_logining, s);
    gtk_widget_show_all(s->l->win);
    gtk_main();
}

void mx_client_init(t_s *s, int argc, char *argv[]){
    gtk_init(&argc, &argv);
    mx_init_logining_1(s);
    mx_init_logining_2(s);
    mx_init_logining_3(s);
    mx_init_logining_4(s);
}








void mx_report_1(time_t t, const char *ocsp_url, t_s *s, char *host) {
    fprintf(stderr, "\nTLS handshake negotiated %s/%s with host %s\n",
            tls_conn_version(s->c->tls), tls_conn_cipher(s->c->tls), host);
    fprintf(stderr, "Peer name: %s\n", host);
    if (tls_peer_cert_subject(s->c->tls))
        fprintf(stderr, "Subject: %s\n",
                tls_peer_cert_subject(s->c->tls));
    if (tls_peer_cert_issuer(s->c->tls))
        fprintf(stderr, "Issuer: %s\n",
                tls_peer_cert_issuer(s->c->tls));
    if ((t = tls_peer_cert_notbefore(s->c->tls)) != -1)
        fprintf(stderr, "Valid From: %s", ctime(&t));
    if ((t = tls_peer_cert_notafter(s->c->tls)) != -1)
        fprintf(stderr, "Valid Until: %s", ctime(&t));
    if (tls_peer_cert_hash(s->c->tls))
        fprintf(stderr, "Cert Hash: %s\n",
                tls_peer_cert_hash(s->c->tls));
    ocsp_url = tls_peer_ocsp_url(s->c->tls);
    if (ocsp_url != NULL)
        fprintf(stderr, "OCSP URL: %s\n", ocsp_url);
}

void mx_report_2(time_t t, t_s *s) {
    fprintf(stderr, "OCSP Stapling: %s\n",
            tls_peer_ocsp_result(s->c->tls) == NULL ?  "" :
            tls_peer_ocsp_result(s->c->tls));
    fprintf(stderr,
            " response_status=%d cert_status=%d crl_reason=%d\n",
            tls_peer_ocsp_response_status(s->c->tls),
            tls_peer_ocsp_cert_status(s->c->tls),
            tls_peer_ocsp_crl_reason(s->c->tls));
    t = tls_peer_ocsp_this_update(s->c->tls);
    fprintf(stderr, "  this update: %s",
            t != -1 ? ctime(&t) : "\n");
    t =  tls_peer_ocsp_next_update(s->c->tls);
    fprintf(stderr, "  next update: %s",
            t != -1 ? ctime(&t) : "\n");
    t =  tls_peer_ocsp_revocation_time(s->c->tls);
    fprintf(stderr, "  revocation: %s",
            t != -1 ? ctime(&t) : "\n");
}

void mx_report_tls_client(t_s *s, char *host) {
    time_t t = 0;
    const char *ocsp_url;

    mx_report_1(t, ocsp_url, s, host);
    switch (tls_peer_ocsp_response_status(s->c->tls)) {
        case TLS_OCSP_RESPONSE_SUCCESSFUL:
            mx_report_2(t, s);
            break;
        case -1:
            break;
        default:
            fprintf(stderr, "OCSP Stapling: fail-response_status %d (%s)\n",
                    tls_peer_ocsp_response_status(s->c->tls),
                    tls_peer_ocsp_result(s->c->tls) == NULL ?  "" :
                    tls_peer_ocsp_result(s->c->tls));
            break;
    }
}




void first_serv_init(t_s *s) {
    s->c->enable = 1;
    if (tls_init() < 0) {
        printf("tls_init error\n");
        exit(1);
    }
    s->c->cnf = tls_config_new();
    s->c->tls = tls_client();
    tls_config_insecure_noverifycert(s->c->cnf);
    tls_config_insecure_noverifyname(s->c->cnf);
    if (tls_config_set_key_file(s->c->cnf, "./certificates/client.key") < 0) {
        printf("tls_config_set_key_file error\n");
        exit(1);
    }
    if (tls_config_set_cert_file(s->c->cnf, 
                                 "./certificates/client.pem") < 0) {
        printf("tls_config_set_cert_file error\n");
        exit(1);
    }
    tls_configure(s->c->tls, s->c->cnf);
    memset(&s->c->h, 0, sizeof(s->c->h));
}

int second_serv_init(t_s *s, char **argv) {
    s->c->h.ai_socktype = SOCK_STREAM;
    if ((s->c->err = getaddrinfo(argv[1], argv[2], 
                                 &s->c->h, &s->c->p_ad)) != 0) {
        fprintf(stderr, "getaddrinfo()fail. (%s)\n", gai_strerror(s->c->err));
        return 1;
    }
    printf("Remote address is: ");
    getnameinfo(s->c->p_ad->ai_addr, s->c->p_ad->ai_addrlen,
                s->c->address_buffer, sizeof(s->c->address_buffer),
                s->c->service_buffer, sizeof(s->c->service_buffer),
                NI_NUMERICHOST);
    printf("%s %s\n", s->c->address_buffer, s->c->service_buffer);
    s->c->sock = socket(s->c->p_ad->ai_family,
                  s->c->p_ad->ai_socktype, s->c->p_ad->ai_protocol);
    if (s->c->sock == -1) {
        printf("error sock = %s\n", strerror(errno));
        return 1;
    }
    return 0;
}

int third_serv_init(t_s *s) {
    setsockopt(s->c->sock, IPPROTO_TCP, SO_KEEPALIVE,
               &s->c->enable, sizeof(int));
    if (connect(s->c->sock, s->c->p_ad->ai_addr, s->c->p_ad->ai_addrlen)) {
        printf("connect error = %s\n", strerror(errno));
        return 1;
    }
    freeaddrinfo(s->c->p_ad);
    printf("connect TCP sock =%d\n", s->c->sock);

    if (tls_connect_socket(s->c->tls, s->c->sock, "uchat_server") < 0) {
        printf("tls_connect error\n");
        printf("%s\n", tls_error(s->c->tls));
        exit(1);
    }
    printf("tls connect +\n");
    return 0;
}

int init_server(t_s *s, char **argv) {
    first_serv_init(s);
    if (second_serv_init(s, argv))
        return 1;
    if (third_serv_init(s))
        return 1;
    if (tls_handshake(s->c->tls) < 0) {
        printf("tls_handshake error\n");
        printf("%s\n", tls_error(s->c->tls));
        exit(1);
    }
    mx_report_tls_client(s, "client");
    printf("\n");
    s->c->rc = 0;
    s->c->pfd[0].fd = 0;
    s->c->pfd[0].events = POLLIN;
    s->c->pfd[1].fd = s->c->sock;
    s->c->pfd[1].events = POLLIN;
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        mx_printerr("usage: uchat [ip_adress] [port]\n");
        return -1;
    }
    t_s *s = malloc(sizeof(t_s));

    s->c = malloc(sizeof(t_clt));
    s->l = malloc(sizeof(t_lgn));
    s->h = malloc(sizeof(t_ct));
    if (init_server(s, argv))
        mx_exit_chat(s);
    mx_client_init(s, argc, argv);
}
