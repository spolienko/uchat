#include "uchat.h"
#include "cJSON.h"

typedef struct s_clt {
    struct addrinfo hints;
    struct addrinfo *peer_address;
    int sock;
    int err;
    int enable;
    struct tls *tls;
    struct tls_config *config;
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
    char *ip;
    char *port;
    char *lang;
    char *theme;
    GtkWidget *window;
    GtkWidget *main_label;
    GtkWidget *username_label;
    GtkWidget *password_label;
    GtkWidget *ip_label;
    GtkWidget *port_label;
    GtkWidget *username_entry;
    GtkWidget *password_entry;
    GtkWidget *error_label;
    GtkWidget *ok_button;
    GtkWidget *vbox;
    GtkWidget *main_label_box;
    GtkWidget *username_box;
    GtkWidget *password_box;
    GtkWidget *error_box;
    GtkWidget *ok_button_box;
    GtkStyleContext *c_window;
    GtkStyleContext *c_main_label;
    GtkStyleContext *c_username_label;
    GtkStyleContext *c_password_label;
    GtkStyleContext *c_username_entry;
    GtkStyleContext *c_password_entry;
    GtkStyleContext *c_error_label;
    GtkStyleContext *c_ok_button;
    GtkCssProvider *cssProvider;
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
    GtkWidget *v_bt_like;
    GtkWidget *v_bt_aut;
    GtkWidget *v_bt_info;
    GtkWidget *v_bt_s1;
    GtkWidget *v_bt_s2;
    GtkWidget *v_bt_s3;
    GtkWidget *v_bt_s4;
    GtkWidget *v_bt_s5;
    GtkWidget *v_bt_s6;
    GtkWidget *vbox;
    GtkWidget *top_b;
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

void do_sending(GtkWidget *widget, t_s *s) {
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


void closeApp(GtkWidget *window, gpointer data)
{
    printf("Destroy\n");
    gtk_main_quit();
    exit(1);
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

void init_chatt(t_s *s) {
    s->h->login = s->l->login;
    s->h->lang = s->l->lang;
    s->h->v_n = 0;
    s->h->theme = s->l->theme;
    printf("%s\t%s\n",s->h->theme ,s->h->lang);
    s->h->v_scroll = gtk_scrolled_window_new(0,0);
    s->h->v_l_btn_ru = gtk_button_new_with_label("RUS");
    s->h->v_l_btn_en = gtk_button_new_with_label("ENG");
    s->h->v_t_btn_b = gtk_button_new_with_label("   ");
    s->h->v_t_btn_w = gtk_button_new_with_label("   ");
    s->h->vbox = gtk_box_new(TRUE, 0);
    s->h->top_b = gtk_box_new(FALSE, 0);
    s->h->scr_box = gtk_box_new(FALSE, 0);
    s->h->ent_box = gtk_box_new(FALSE, 0);
    s->h->btns_b = gtk_box_new(FALSE, 0);
    s->h->v_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    s->h->cssProv = gtk_css_provider_new();

    s->h->v_listbox = gtk_list_box_new();
    s->h->v_main_e = gtk_entry_new();
    s->h->v_bt_e = gtk_button_new_with_label("Send");
    s->h->v_bt_info = gtk_button_new_with_label("Info");
    s->h->v_bt_like = gtk_button_new_with_label("Love");
    s->h->v_bt_aut = gtk_button_new_with_label(":()");
    s->h->v_bt_s1 = gtk_button_new_with_label("+");
    s->h->v_bt_s2 = gtk_button_new_with_label("sadness");
    s->h->v_bt_s3 = gtk_button_new_with_label("danger");
    s->h->v_bt_s4 = gtk_button_new_with_label("sad cat");
    s->h->v_bt_s5 = gtk_button_new_with_label("?");
    s->h->v_bt_s6 = gtk_button_new_with_label("hello");

    gtk_box_pack_start(GTK_BOX(s->h->top_b), s->h->v_l_btn_ru, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->top_b), s->h->v_l_btn_en, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->top_b), s->h->v_t_btn_b, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->top_b), s->h->v_t_btn_w, FALSE, TRUE, 0);
    gtk_widget_set_size_request(s->h->v_l_btn_ru,450,50);
    gtk_widget_set_size_request(s->h->v_l_btn_en,450,50);
    gtk_widget_set_size_request(s->h->v_t_btn_b,450,50);
    gtk_widget_set_size_request(s->h->v_t_btn_w,450,50);

    gtk_box_pack_start(GTK_BOX(s->h->vbox), s->h->top_b, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->vbox), s->h->scr_box, FALSE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(s->h->v_window), s->h->vbox);
    gtk_window_set_resizable((GtkWindow *)s->h->v_window, FALSE);
    gtk_box_pack_start(GTK_BOX(s->h->scr_box), s->h->v_scroll, TRUE, TRUE, 0);
    gtk_widget_set_size_request(s->h->v_scroll,1800,950);
    gtk_box_pack_start(GTK_BOX(s->h->ent_box), s->h->v_main_e, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->ent_box), s->h->v_bt_e, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->vbox), s->h->ent_box, TRUE, FALSE, 0);
    g_signal_connect(G_OBJECT(s->h->v_bt_e), "clicked", G_CALLBACK(do_sending), s);
    gtk_widget_set_size_request(s->h->v_bt_e,200,50);
    
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_info, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_like, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_aut, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_s1, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_s2, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_s3, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_s4, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_s5, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(s->h->btns_b), s->h->v_bt_s6, FALSE, TRUE, 0);
    gtk_widget_set_size_request(s->h->v_bt_info,200,50);
    gtk_widget_set_size_request(s->h->v_bt_like,200,50);
    gtk_widget_set_size_request(s->h->v_bt_aut,200,50);
    gtk_widget_set_size_request(s->h->v_bt_s1,200,50);
    gtk_widget_set_size_request(s->h->v_bt_s2,200,50);
    gtk_widget_set_size_request(s->h->v_bt_s3,200,50);
    gtk_widget_set_size_request(s->h->v_bt_s4,200,50);
    gtk_widget_set_size_request(s->h->v_bt_s5,200,50);
    gtk_widget_set_size_request(s->h->v_bt_s6,200,50);

    gtk_box_pack_start(GTK_BOX(s->h->vbox), s->h->btns_b, TRUE, FALSE, 0);
    s->h->c_v_window = gtk_widget_get_style_context(s->h->v_window);
    s->h->c_v_l_btn_ru = gtk_widget_get_style_context(s->h->v_l_btn_ru);
    s->h->c_v_l_btn_en = gtk_widget_get_style_context(s->h->v_l_btn_en);
    s->h->c_v_t_btn_b = gtk_widget_get_style_context(s->h->v_t_btn_b);
    s->h->c_v_t_btn_w = gtk_widget_get_style_context(s->h->v_t_btn_w);
    s->h->c_v_scroll = gtk_widget_get_style_context(s->h->v_scroll);
    s->h->c_v_main_e = gtk_widget_get_style_context(s->h->v_main_e);
    s->h->c_v_bt_e = gtk_widget_get_style_context(s->h->v_bt_e);
    s->h->c_v_bt_like = gtk_widget_get_style_context(s->h->v_bt_like);
    s->h->c_v_bt_aut = gtk_widget_get_style_context(s->h->v_bt_aut);
    s->h->c_v_bt_info = gtk_widget_get_style_context(s->h->v_bt_info);
    s->h->c_v_bt_s1 = gtk_widget_get_style_context(s->h->v_bt_s1);
    s->h->c_v_bt_s2 = gtk_widget_get_style_context(s->h->v_bt_s2);
    s->h->c_v_bt_s3 = gtk_widget_get_style_context(s->h->v_bt_s3);
    s->h->c_v_bt_s4 = gtk_widget_get_style_context(s->h->v_bt_s4);
    s->h->c_v_bt_s5 = gtk_widget_get_style_context(s->h->v_bt_s5);
    s->h->c_v_bt_s6 = gtk_widget_get_style_context(s->h->v_bt_s6);

    g_signal_connect(G_OBJECT(s->h->v_bt_info), "clicked", G_CALLBACK(inf), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_like), "clicked", G_CALLBACK(sen), (gpointer)0);
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
}





void do_logining(GtkWidget *widget, t_s *s) {
    pthread_t loginner;
    char *login = gtk_entry_get_text(GTK_ENTRY(s->l->username_entry));
    if(!login || !*login) {
            gtk_label_set_text(s->l->error_label, "Something went wrong");
        return;
    }
    char *password = gtk_entry_get_text(GTK_ENTRY(s->l->password_entry));
    if(!password || !*password) {
            gtk_label_set_text(s->l->error_label, "Something went wrong");
        return;
    }
    
    s->l->login = login;
    s->l->pass = password;
    printf("%s\n", password);
    cJSON *send = cJSON_CreateObject();
    char *res;
    cJSON_AddStringToObject(send, "kind", "login");
    cJSON_AddStringToObject(send, "login", s->l->login);
    cJSON_AddStringToObject(send, "pasword", s->l->pass);
    res = cJSON_Print(send);
    printf("%s\n", res);
    tls_write(s->c->tls, res, strlen(res) + 1);
    while (true) {
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
            cJSON *msg = cJSON_Parse(s->c->bufs);
            s->l->login_in = cJSON_GetObjectItemCaseSensitive(msg, "status")->valueint;
            s->l->lang = cJSON_GetObjectItemCaseSensitive(msg, "lang")->valuestring;
            s->l->theme = cJSON_GetObjectItemCaseSensitive(msg, "tema")->valuestring;
            return;
        }
        
    }
}

gboolean check_logining(t_s *s)
{
    if(s->l->login_in) {
        s->l->login_in = 0;
        gtk_widget_hide(s->l->window);
        init_chatt(s);
        return G_SOURCE_REMOVE;
    }
    return G_SOURCE_CONTINUE;
}

void mx_client_init(t_s *s, int argc, char *argv[]){
    gtk_init(&argc, &argv);
    s->l->login_in = 0;
    s->l->login = "";
    s->l->pass = "";
    s->l->ip = "";
    s->l->port = "";
    s->l->lang = "ENG";
    s->l->theme = "BLACK";
    s->l->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    s->l->main_label = gtk_label_new("Uchat");
    s->l->username_label = gtk_label_new("Login:");
    s->l->password_label = gtk_label_new("Password:");
    s->l->error_label = gtk_label_new("");
    s->l->username_entry = gtk_entry_new();
    s->l->password_entry = gtk_entry_new();
    s->l->ok_button = gtk_button_new_with_label("Enter");
    gtk_entry_set_text(GTK_ENTRY(s->l->username_entry), "admin");
    gtk_entry_set_text(GTK_ENTRY(s->l->password_entry), "admin");



    s->l->vbox = gtk_box_new(TRUE, 0);
    s->l->main_label_box = gtk_hbox_new(TRUE, 10);
    s->l->username_box = gtk_hbox_new(TRUE, 10);
    s->l->password_box = gtk_hbox_new(TRUE, 10);
    s->l->error_box = gtk_hbox_new(TRUE, 10);
    s->l->ok_button_box = gtk_hbox_new(TRUE, 10);
    s->l->cssProvider = gtk_css_provider_new();
    gtk_widget_show_all(s->l->window);
    gtk_window_set_position(GTK_WINDOW(s->l->window), GTK_WIN_POS_CENTER);
    gtk_entry_set_visibility(GTK_ENTRY(s->l->password_entry), FALSE);
    gtk_window_set_resizable (GTK_WINDOW(s->l->window), FALSE);
    gtk_css_provider_load_from_path(s->l->cssProvider,
                                    "client/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(s->l->cssProvider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_set_title(GTK_WINDOW(s->l->window), "Uchat");
    
    g_signal_connect(G_OBJECT(s->l->window), "destroy", G_CALLBACK(closeApp), NULL);
    s->l->c_window = gtk_widget_get_style_context(s->l->window);
    s->l->c_main_label = gtk_widget_get_style_context(s->l->main_label);
    s->l->c_username_label = gtk_widget_get_style_context(s->l->username_label);
    s->l->c_password_label = gtk_widget_get_style_context(s->l->password_label);
    s->l->c_username_entry = gtk_widget_get_style_context(s->l->username_entry);
    s->l->c_password_entry = gtk_widget_get_style_context(s->l->password_entry);
    s->l->c_error_label = gtk_widget_get_style_context(s->l->error_label);
    s->l->c_ok_button = gtk_widget_get_style_context(s->l->ok_button);
   

    gtk_style_context_add_class (s->l->c_window, "black");
    gtk_style_context_add_class (s->l->c_main_label, "black");
    gtk_style_context_add_class (s->l->c_username_label, "black");
    gtk_style_context_add_class (s->l->c_password_label, "black");
    gtk_style_context_add_class (s->l->c_username_entry, "black");
    gtk_style_context_add_class (s->l->c_password_entry, "black");
    gtk_style_context_add_class (s->l->c_ok_button, "black");

    gtk_style_context_add_class (s->l->c_ok_button, "ok_btn");
    gtk_style_context_add_class (s->l->c_main_label, "main_label");
    gtk_style_context_add_class (s->l->c_error_label, "error");



    gtk_box_pack_start(GTK_BOX(s->l->main_label_box), s->l->main_label, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->username_box), s->l->username_label, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->username_box), s->l->username_entry, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->password_box), s->l->password_label, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->password_box), s->l->password_entry, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->error_box), s->l->error_label, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->ok_button_box), s->l->ok_button, TRUE, TRUE, 10);

    
    gtk_box_pack_start(GTK_BOX(s->l->vbox), s->l->main_label_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->vbox), s->l->username_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->vbox), s->l->password_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->vbox), s->l->error_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(s->l->vbox), s->l->ok_button_box, TRUE, TRUE, 10);
    g_signal_connect(G_OBJECT(s->l->ok_button), "clicked", G_CALLBACK(do_logining), s);
    gtk_container_add(GTK_CONTAINER(s->l->window ), s->l->vbox);
    g_timeout_add(50, check_logining, s);
    gtk_widget_show_all(s->l->window);
    gtk_main();
}

void mx_report_tls_client(t_s *s, char * host) {
    time_t t;
    const char *ocsp_url;

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
    switch (tls_peer_ocsp_response_status(s->c->tls)) {
        case TLS_OCSP_RESPONSE_SUCCESSFUL:
            fprintf(stderr, "OCSP Stapling: %s\n",
                    tls_peer_ocsp_result(s->c->tls) == NULL ?  "" :
                    tls_peer_ocsp_result(s->c->tls));
            fprintf(stderr,
                    "  response_status=%d cert_status=%d crl_reason=%d\n",
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
            break;
        case -1:
            break;
        default:
            fprintf(stderr, "OCSP Stapling:  failure - response_status %d (%s)\n",
                    tls_peer_ocsp_response_status(s->c->tls),
                    tls_peer_ocsp_result(s->c->tls) == NULL ?  "" :
                    tls_peer_ocsp_result(s->c->tls));
            break;

    }
}

int init_server(t_s *s, char **argv) {

    s->c->enable = 1;


    
    if (tls_init() < 0) {
        printf("tls_init error\n");
        exit(1);
    }


    s->c->config = tls_config_new();
    s->c->tls = tls_client();
    tls_config_insecure_noverifycert(s->c->config);
    tls_config_insecure_noverifyname(s->c->config);

    if (tls_config_set_key_file(s->c->config, "./certificates/client.key") < 0) {
        printf("tls_config_set_key_file error\n");
        exit(1);
    }

    if (tls_config_set_cert_file(s->c->config, "./certificates/client.pem") < 0) {
        printf("tls_config_set_cert_file error\n");
        exit(1);
    }

    tls_configure(s->c->tls, s->c->config);

    memset(&s->c->hints, 0, sizeof(s->c->hints));
    s->c->hints.ai_socktype = SOCK_STREAM;
    if ((s->c->err = getaddrinfo(argv[1], argv[2], &s->c->hints, &s->c->peer_address)) != 0) {
        fprintf(stderr, "getaddrinfo() failed. (%s)\n", gai_strerror(s->c->err));
        return 1;
    }
    printf("Remote address is: ");
    
    getnameinfo(s->c->peer_address->ai_addr, s->c->peer_address->ai_addrlen,
                s->c->address_buffer, sizeof(s->c->address_buffer),
                s->c->service_buffer, sizeof(s->c->service_buffer),
                NI_NUMERICHOST);
    printf("%s %s\n", s->c->address_buffer, s->c->service_buffer);

    s->c->sock = socket(s->c->peer_address->ai_family,
                  s->c->peer_address->ai_socktype, s->c->peer_address->ai_protocol);
    if (s->c->sock == -1) {
        printf("error sock = %s\n", strerror(errno));
        return 1;
    }
    setsockopt(s->c->sock, IPPROTO_TCP, SO_KEEPALIVE, &s->c->enable, sizeof(int));
    if (connect(s->c->sock, s->c->peer_address->ai_addr, s->c->peer_address->ai_addrlen)) {
        printf("connect error = %s\n", strerror(errno));
        return 1;
    }
    freeaddrinfo(s->c->peer_address);
    printf("connect TCP sock =%d\n", s->c->sock);

    if (tls_connect_socket(s->c->tls, s->c->sock, "uchat_server") < 0) {
        printf("tls_connect error\n");
        printf("%s\n", tls_error(s->c->tls));
        exit(1);
    }
    printf("tls connect +\n");
    if (tls_handshake(s->c->tls) < 0) {
        printf("tls_handshake error\n");
        printf("%s\n", tls_error(s->c->tls));
        exit(1);
    }
    mx_report_tls_client(s, "client");
    printf("\n");
    // tls_write(s->c->tls, "TLS connect", strlen("TLS connect"));
    
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
        exit(1);
    
    mx_client_init(s, argc, argv);
    
    tls_close(s->c->tls);
    tls_free(s->c->tls);
    tls_config_free(s->c->config);
    printf("Closing socket...\n");
    close(s->c->sock);
    printf("exit client\n");
    return 0;

}

