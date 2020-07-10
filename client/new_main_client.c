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
    GtkWidget *v_window;
    GtkWidget *v_main_grid;
    GtkWidget *v_l_btn_ru;
    GtkWidget *v_l_btn_en;
    GtkWidget *v_t_btn_b;
    GtkWidget *v_t_btn_w;
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

char *help_str(){
    char *sss = "Rules: max str len 100 chars\n"
        "Comands write only: \\cmd\\"
        "Editing: \\123\\ - font-size, \\rol\\ - color, \\inb\\ - fonts\n"
        "Stickers: \\++++\\,\n"
        "Special cmds: \\k[id]\\";
    
    return sss;
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
    gtk_style_context_add_class (inf->c_v_body, "orange");
    gtk_style_context_add_class (inf->c_v_body, "h2");
    gtk_style_context_add_class (inf->c_v_body, "normal");
    gtk_style_context_add_class (inf->c_v_body, "pading_left_100");
}

void init_help(t_inf_row *inf, t_s *s) {
    char *str = help_str();

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

char *what_return(int gg) {
    if (gg == 0)
        return "\\love\\";
    if (gg == 1)
        return "\\aut\\";
    if (gg == 2)
        return "\\++++\\";
    if (gg == 3)
        return "\\sadness\\";
    if (gg == 4)
        return "\\danger\\";
    if (gg == 5)
        return "\\sad_cat\\";
    if (gg == 6)
        return "\\????\\";
    if (gg == 7)
        return "\\hello\\";
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
    gtk_container_add(GTK_CONTAINER(row->v_row), row->v_hrow);
    row->v_author = gtk_label_new(inf->author);
    gtk_box_pack_start(GTK_BOX(row->v_hrow), row->v_author, FALSE, FALSE, 0);
    gtk_widget_set_size_request(row->v_author,250,10);
    gtk_label_set_xalign((GtkLabel *)row->v_author, 0.5);
    row->v_time = gtk_label_new(inf->timebuf);
    gtk_box_pack_start(GTK_BOX(row->v_hrow), row->v_time, FALSE, FALSE, 0);
    gtk_widget_set_size_request(row->v_time,250,10);
    gtk_label_set_xalign((GtkLabel *)row->v_time, 0.5);
}

void end_initing(t_row *row, t_info *inf, t_s *s) {
    (void)inf,(void) s;
    gtk_box_pack_start(GTK_BOX(row->v_hrow), row->v_body, FALSE, FALSE, 0);
    gtk_widget_set_size_request(row->v_body,1300,30);
    // if(!check_on_cmd(inf->body))
    //     gtk_label_set_xalign((GtkLabel *)row->v_body, 0.04);
    gtk_widget_set_size_request(row->v_body,80,30);
    // print_X(row, inf, chat);
    // set_class_for_elem(row, inf, chat);
}

void create_row(t_info *inf, t_s *s) {   
    t_row *row = malloc(sizeof(t_row));

    init_row(row, inf, s);
    // if (check_on_cmd(inf->body)) {
    //     print_cmd(row, inf, chat);
    // }
    // else if (!check_on_cmd(inf->body)) {
        // char *new_body = get_new_body(inf->body);
        row->v_body = gtk_label_new(inf->body);
    // }
    end_initing(row, inf, s);
    gtk_widget_show_all(s->h->v_window);
}

gboolean check_chat(t_s *s)
{
     bzero(s->c->bufs, 1000);
        bzero(s->c->bufc, 1000);

        poll(s->c->pfd, 2, -1);
        // if (s->c->pfd[0].revents & POLLIN) {
        //     int q = read(0, s->c->bufc, 1000);
        //     printf("%d\n",q);
        //     tls_write(s->c->tls, s->c->bufc, q);
        // }

        if (s->c->pfd[1].revents & POLLIN) {
            if ((s->c->rc = tls_read(s->c->tls, s->c->bufs, 1000)) <= 0) return G_SOURCE_CONTINUE;
            // printf("Mesage (%lu): %s\n", s->c->rc, s->c->bufs);
            // printf("%s\n",s->c->bufs);
            

            // s->l->login_in = cJSON_GetObjectItemCaseSensitive(msg, "status")->valueint;
            // s->l->lang = cJSON_GetObjectItemCaseSensitive(msg, "lang")->valuestring;
            // s->l->theme = cJSON_GetObjectItemCaseSensitive(msg, "tema")->valuestring;
            return G_SOURCE_REMOVE; 
        }
    return G_SOURCE_CONTINUE;
}


void watcher_thread(t_s *s) {
    // message_request_history(10);
    // while(1) {
    //     t_info *inf = malloc(sizeof(t_info));
    //     struct timeval tv;
    //     int k = message_receive(&tv, &inf->author, &inf->body);
    //     struct tm *nowtm;

    //     if (auditor_watcher(inf, k) == 1)
    //         continue;
    //     else if (auditor_watcher(inf, k) == 0)
    //         break;
    //     if(tv.tv_sec) {
    //         nowtm = localtime(&tv.tv_sec);
    //         strftime(inf->timebuf, 64, "[%d.%m.%Y %H:%M:%S]", nowtm);
    //     }
    //     else
    //         *inf->timebuf = 0;
    //     create_row(inf, chat);
    // }

    while (true)
    {
        bzero(s->c->bufs, 1000);
        bzero(s->c->bufc, 1000);

        poll(s->c->pfd, 2, -1);
        // if (s->c->pfd[0].revents & POLLIN) {
        //     int q = read(0, s->c->bufc, 1000);
        //     printf("%d\n",q);
        //     tls_write(s->c->tls, s->c->bufc, q);
        // }

        if (s->c->pfd[1].revents & POLLIN) {
            
            if ((s->c->rc = tls_read(s->c->tls, s->c->bufs, 1000)) <= 0) break;
            // printf("Mesage (%lu): %s\n", s->c->rc, s->c->bufs);
            t_info *inf = malloc(sizeof(t_info));
            cJSON *msg = cJSON_Parse(s->c->bufs);
            inf->author = cJSON_GetObjectItemCaseSensitive(msg, "login")->valuestring;
            inf->body = cJSON_GetObjectItemCaseSensitive(msg, "msg")->valuestring;
            inf->timebuf = cJSON_GetObjectItemCaseSensitive(msg, "time")->valuestring;
            create_row(inf, s);
            // printf("%s\n",s->c->bufs);
            // cJSON *msg = cJSON_Parse(s->c->bufs);
            // s->l->login_in = cJSON_GetObjectItemCaseSensitive(msg, "status")->valueint;
            // s->l->lang = cJSON_GetObjectItemCaseSensitive(msg, "lang")->valuestring;
            // s->l->theme = cJSON_GetObjectItemCaseSensitive(msg, "tema")->valuestring;
        }
    }


    return;
}


// void create_content(t_s *s) {
//     if(!strcmp(s->h->theme, "eng"))
//         create_eng(s);
//     if(!strcmp(s->h->theme, "rus")){
//         create_rus(s);
//         return;
//     }
        
// }

void mx_init_chat1(t_s *s) {
    s->h->login = s->l->login;
    s->h->lang = s->l->lang;
    s->h->v_n = 0;
    s->h->theme = s->l->theme;
    // create_content(s);
    s->h->v_scroll = gtk_scrolled_window_new(0,0);
    s->h->v_l_btn_ru = gtk_button_new_with_label("RUS");
    s->h->v_l_btn_en = gtk_button_new_with_label("ENG");
    s->h->v_t_btn_b = gtk_button_new_with_label("   ");
    s->h->v_t_btn_w = gtk_button_new_with_label("   ");
    s->h->vbox = gtk_box_new(TRUE, 0);
    s->h->T_b = gtk_box_new(FALSE, 0);
    s->h->scr_box = gtk_box_new(FALSE, 0);
    s->h->ent_box = gtk_box_new(FALSE, 0);
    s->h->btns_b = gtk_box_new(FALSE, 0);
    s->h->v_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    s->h->cssProv = gtk_css_provider_new();
}

void mx_init_chat2(t_s *s) {
    printf("%s\t%s\n",s->h->lang , s->h->theme);
    s->h->v_listbox = gtk_list_box_new();
    s->h->v_main_e = gtk_entry_new();
    s->h->v_bt_e = gtk_button_new_with_label("Send");
    s->h->v_bt_inf = gtk_button_new_with_label("Info");
    s->h->v_bt_lik = gtk_button_new_with_label("Love");
    s->h->v_bt_aut = gtk_button_new_with_label(":()");
    s->h->v_bt_s1 = gtk_button_new_with_label("+");
    s->h->v_bt_s2 = gtk_button_new_with_label("sadness");
    s->h->v_bt_s3 = gtk_button_new_with_label("danger");
    s->h->v_bt_s4 = gtk_button_new_with_label("sad cat");
    s->h->v_bt_s5 = gtk_button_new_with_label("?");
    s->h->v_bt_s6 = gtk_button_new_with_label("hello");
    gtk_box_pack_start(GTK_BOX(s->h->T_b), s->h->v_l_btn_ru, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->T_b), s->h->v_l_btn_en, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->T_b), s->h->v_t_btn_b, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->T_b), s->h->v_t_btn_w, FALSE, TRUE, 0);
}

void mx_init_chat3(t_s *s) {
    gtk_widget_set_size_request(s->h->v_l_btn_ru, 450, 50);
    gtk_widget_set_size_request(s->h->v_l_btn_en, 450, 50);
    gtk_widget_set_size_request(s->h->v_t_btn_b, 450, 50);
    gtk_widget_set_size_request(s->h->v_t_btn_w, 450, 50);
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


void mx_init_chat4(t_s *s) {
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
}

void init_chatt(t_s *s) {
    mx_init_chat1(s);
    mx_init_chat2(s);
    mx_init_chat3(s);
    
    
    

    gtk_box_pack_start(GTK_BOX(s->h->vbox), s->h->btns_b, TRUE, FALSE, 0);
    s->h->c_v_window = gtk_widget_get_style_context(s->h->v_window);
    s->h->c_v_l_btn_ru = gtk_widget_get_style_context(s->h->v_l_btn_ru);
    s->h->c_v_l_btn_en = gtk_widget_get_style_context(s->h->v_l_btn_en);
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

    // g_timeout_add(50, check_chat, s);
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
    gtk_style_context_add_class (s->l->c_window, "lw");
    gtk_style_context_add_class (s->l->c_main_label, "bl");
    gtk_style_context_add_class (s->l->c_user_lbl, "bl");
    gtk_style_context_add_class (s->l->c_pass_lbl, "bl");
    gtk_style_context_add_class (s->l->c_user_ety, "bl");
    gtk_style_context_add_class (s->l->c_pass_ety, "bl");
    gtk_style_context_add_class (s->l->c_ok_button, "bl");
    gtk_style_context_add_class (s->l->c_ok_button, "ok_btn");
    gtk_style_context_add_class (s->l->c_main_label, "main_l");
    gtk_style_context_add_class (s->l->c_error_label, "error");
    gtk_style_context_add_class (s->l->c_user_ety, "lent");
    gtk_style_context_add_class (s->l->c_pass_ety, "lent");
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
