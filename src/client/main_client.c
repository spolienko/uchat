#include "uchat.h"
#include "cJSON.h"

void closeApp(GtkWidget *window, gpointer data)
{
    printf("Destroy\n");
    gtk_main_quit();
    exit(1);
}


typedef struct s_login {
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
}              t_login;





typedef struct s_client {
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
}              t_client;

typedef struct s_s {
    t_client *c;
    t_login *logining;
}              t_s;

















typedef struct s_chat {
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
}              t_chat;

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

// void check_lang(t_chat *chat){
//     if(!strcmp(logining->lang, "eng")){

//     }
// }


char *strnew(int size) {
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}

int *watcher_thread(t_chat *chat);

void do_sending(GtkWidget *widget, t_chat *chat) {
    char *message;
    message = (char *)gtk_entry_get_text(GTK_ENTRY(chat->v_main_e));
    if(!message || !*message)
        return;
    char *m = malloc(strlen(message) + 1);    
    strcpy(m, trim(message));
    gtk_entry_set_text(GTK_ENTRY(chat->v_main_e), "");
    if (strlen(m) < 100 && strlen(m) > 0)
    // message_send(m);
    printf("%s\n", m);
    else {
        printf("to manywords\n");
    }
    (void)widget;
}

void first_init (t_s *s, t_chat *chat) {
    chat->login = s->logining->login;
    chat->lang = s->logining->lang;
    chat->v_n = 0;
    chat->theme = s->logining->theme;
    chat->v_scroll = gtk_scrolled_window_new(0,0);
    chat->v_l_btn_ru = gtk_button_new_with_label("RUS");
    chat->v_l_btn_en = gtk_button_new_with_label("ENG");
    chat->v_t_btn_b = gtk_button_new_with_label("   ");
    chat->v_t_btn_w = gtk_button_new_with_label("   ");
    chat->vbox = gtk_box_new(TRUE, 0);
    chat->top_b = gtk_box_new(FALSE, 0);
    chat->scr_box = gtk_box_new(FALSE, 0);
    chat->ent_box = gtk_box_new(FALSE, 0);
    chat->btns_b = gtk_box_new(FALSE, 0);
    chat->v_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    chat->cssProv = gtk_css_provider_new();
}

void header_btns_init (t_chat *chat) {
    gtk_box_pack_start(GTK_BOX(chat->top_b), chat->v_l_btn_ru, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->top_b), chat->v_l_btn_en, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->top_b), chat->v_t_btn_b, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->top_b), chat->v_t_btn_w, FALSE, TRUE, 0);
    gtk_widget_set_size_request(chat->v_l_btn_ru,450,50);
    gtk_widget_set_size_request(chat->v_l_btn_en,450,50);
    gtk_widget_set_size_request(chat->v_t_btn_b,450,50);
    gtk_widget_set_size_request(chat->v_t_btn_w,450,50);
}

void second_init (t_chat *chat) {
    chat->v_listbox = gtk_list_box_new();
    chat->v_main_e = gtk_entry_new();
    chat->v_bt_e = gtk_button_new_with_label("Send");
    chat->v_bt_info = gtk_button_new_with_label("Info");
    chat->v_bt_like = gtk_button_new_with_label("Love");
    chat->v_bt_aut = gtk_button_new_with_label(":()");
    chat->v_bt_s1 = gtk_button_new_with_label("+");
    chat->v_bt_s2 = gtk_button_new_with_label("sadness");
    chat->v_bt_s3 = gtk_button_new_with_label("danger");
    chat->v_bt_s4 = gtk_button_new_with_label("sad cat");
    chat->v_bt_s5 = gtk_button_new_with_label("?");
    chat->v_bt_s6 = gtk_button_new_with_label("hello");
    header_btns_init (chat);
    gtk_box_pack_start(GTK_BOX(chat->vbox), chat->top_b, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->vbox), chat->scr_box, FALSE, TRUE, 0);
}

void footer_btns_init (t_chat *chat) {
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_info, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_like, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_aut, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_s1, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_s2, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_s3, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_s4, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_s5, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_s6, FALSE, TRUE, 0);
    gtk_widget_set_size_request(chat->v_bt_info,200,50);
    gtk_widget_set_size_request(chat->v_bt_like,200,50);
    gtk_widget_set_size_request(chat->v_bt_aut,200,50);
    gtk_widget_set_size_request(chat->v_bt_s1,200,50);
    gtk_widget_set_size_request(chat->v_bt_s2,200,50);
    gtk_widget_set_size_request(chat->v_bt_s3,200,50);
    gtk_widget_set_size_request(chat->v_bt_s4,200,50);
    gtk_widget_set_size_request(chat->v_bt_s5,200,50);
    gtk_widget_set_size_request(chat->v_bt_s6,200,50);
}
void third_init (t_chat *chat) {
    gtk_container_add(GTK_CONTAINER(chat->v_window), chat->vbox);
    gtk_window_set_resizable((GtkWindow *)chat->v_window, FALSE);
    gtk_box_pack_start(GTK_BOX(chat->scr_box), chat->v_scroll, TRUE, TRUE, 0);
    gtk_widget_set_size_request(chat->v_scroll,1800,950);
    gtk_box_pack_start(GTK_BOX(chat->ent_box), chat->v_main_e, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->ent_box), chat->v_bt_e, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chat->vbox), chat->ent_box, TRUE, FALSE, 0);
    g_signal_connect(G_OBJECT(chat->v_bt_e), "clicked", G_CALLBACK(do_sending),
        chat);
    gtk_widget_set_size_request(chat->v_bt_e,200,50);
    footer_btns_init (chat);
}




void inf(GtkWidget *widget, t_chat *chat);



void init_clicks (t_chat *chat) {
    g_signal_connect(G_OBJECT(chat->v_bt_info), "clicked", G_CALLBACK(inf),
        chat);
    g_signal_connect(G_OBJECT(chat->v_bt_like), "clicked", G_CALLBACK(sen), (gpointer)0);
    g_signal_connect(G_OBJECT(chat->v_bt_aut), "clicked", G_CALLBACK(sen), (gpointer)1);
    g_signal_connect(G_OBJECT(chat->v_bt_s1), "clicked", G_CALLBACK(sen), (gpointer)2);
    g_signal_connect(G_OBJECT(chat->v_bt_s2), "clicked", G_CALLBACK(sen), (gpointer)3);
    g_signal_connect(G_OBJECT(chat->v_bt_s3), "clicked", G_CALLBACK(sen), (gpointer)4);
    g_signal_connect(G_OBJECT(chat->v_bt_s4), "clicked", G_CALLBACK(sen), (gpointer)5);
    g_signal_connect(G_OBJECT(chat->v_bt_s5), "clicked", G_CALLBACK(sen), (gpointer)6);
    g_signal_connect(G_OBJECT(chat->v_bt_s6), "clicked", G_CALLBACK(sen), (gpointer)7);
}



void initing_chat (t_s *s, t_chat *chat) {
    first_init(s, chat);
    second_init(chat);
    third_init(chat);
    init_clicks(chat);
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
    
    t_chat *chat = malloc(sizeof(t_chat));
    printf("%s\t%s\n",s->logining->lang, s->logining->theme);
    
    // initing_chat (s, chat);
    chat->login = s->logining->login;
    chat->lang = s->logining->lang;
    chat->v_n = 0;
    chat->theme = s->logining->theme;
    chat->v_scroll = gtk_scrolled_window_new(0,0);
    chat->v_l_btn_ru = gtk_button_new_with_label("RUS");
    chat->v_l_btn_en = gtk_button_new_with_label("ENG");
    chat->v_t_btn_b = gtk_button_new_with_label("   ");
    chat->v_t_btn_w = gtk_button_new_with_label("   ");
    chat->vbox = gtk_box_new(TRUE, 0);
    chat->top_b = gtk_box_new(FALSE, 0);
    chat->scr_box = gtk_box_new(FALSE, 0);
    chat->ent_box = gtk_box_new(FALSE, 0);
    chat->btns_b = gtk_box_new(FALSE, 0);
    chat->v_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    chat->cssProv = gtk_css_provider_new();

    chat->v_listbox = gtk_list_box_new();
    chat->v_main_e = gtk_entry_new();
    chat->v_bt_e = gtk_button_new_with_label("Send");
    chat->v_bt_info = gtk_button_new_with_label("Info");
    chat->v_bt_like = gtk_button_new_with_label("Love");
    chat->v_bt_aut = gtk_button_new_with_label(":()");
    chat->v_bt_s1 = gtk_button_new_with_label("+");
    chat->v_bt_s2 = gtk_button_new_with_label("sadness");
    chat->v_bt_s3 = gtk_button_new_with_label("danger");
    chat->v_bt_s4 = gtk_button_new_with_label("sad cat");
    chat->v_bt_s5 = gtk_button_new_with_label("?");
    chat->v_bt_s6 = gtk_button_new_with_label("hello");

    gtk_box_pack_start(GTK_BOX(chat->top_b), chat->v_l_btn_ru, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->top_b), chat->v_l_btn_en, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->top_b), chat->v_t_btn_b, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->top_b), chat->v_t_btn_w, FALSE, TRUE, 0);
    gtk_widget_set_size_request(chat->v_l_btn_ru,450,50);
    gtk_widget_set_size_request(chat->v_l_btn_en,450,50);
    gtk_widget_set_size_request(chat->v_t_btn_b,450,50);
    gtk_widget_set_size_request(chat->v_t_btn_w,450,50);

    gtk_box_pack_start(GTK_BOX(chat->vbox), chat->top_b, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->vbox), chat->scr_box, FALSE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(chat->v_window), chat->vbox);
    gtk_window_set_resizable((GtkWindow *)chat->v_window, FALSE);
    gtk_box_pack_start(GTK_BOX(chat->scr_box), chat->v_scroll, TRUE, TRUE, 0);
    gtk_widget_set_size_request(chat->v_scroll,1800,950);
    gtk_box_pack_start(GTK_BOX(chat->ent_box), chat->v_main_e, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->ent_box), chat->v_bt_e, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chat->vbox), chat->ent_box, TRUE, FALSE, 0);
    g_signal_connect(G_OBJECT(chat->v_bt_e), "clicked", G_CALLBACK(do_sending),
        chat);
    gtk_widget_set_size_request(chat->v_bt_e,200,50);
    footer_btns_init (chat);
    
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_info, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_like, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_aut, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_s1, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_s2, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_s3, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_s4, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_s5, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat->btns_b), chat->v_bt_s6, FALSE, TRUE, 0);
    gtk_widget_set_size_request(chat->v_bt_info,200,50);
    gtk_widget_set_size_request(chat->v_bt_like,200,50);
    gtk_widget_set_size_request(chat->v_bt_aut,200,50);
    gtk_widget_set_size_request(chat->v_bt_s1,200,50);
    gtk_widget_set_size_request(chat->v_bt_s2,200,50);
    gtk_widget_set_size_request(chat->v_bt_s3,200,50);
    gtk_widget_set_size_request(chat->v_bt_s4,200,50);
    gtk_widget_set_size_request(chat->v_bt_s5,200,50);
    gtk_widget_set_size_request(chat->v_bt_s6,200,50);

    gtk_box_pack_start(GTK_BOX(chat->vbox), chat->btns_b, TRUE, FALSE, 0);
    chat->c_v_window = gtk_widget_get_style_context(chat->v_window);
    chat->c_v_l_btn_ru = gtk_widget_get_style_context(chat->v_l_btn_ru);
    chat->c_v_l_btn_en = gtk_widget_get_style_context(chat->v_l_btn_en);
    chat->c_v_t_btn_b = gtk_widget_get_style_context(chat->v_t_btn_b);
    chat->c_v_t_btn_w = gtk_widget_get_style_context(chat->v_t_btn_w);
    chat->c_v_scroll = gtk_widget_get_style_context(chat->v_scroll);
    chat->c_v_main_e = gtk_widget_get_style_context(chat->v_main_e);
    chat->c_v_bt_e = gtk_widget_get_style_context(chat->v_bt_e);
    chat->c_v_bt_like = gtk_widget_get_style_context(chat->v_bt_like);
    chat->c_v_bt_aut = gtk_widget_get_style_context(chat->v_bt_aut);
    chat->c_v_bt_info = gtk_widget_get_style_context(chat->v_bt_info);
    chat->c_v_bt_s1 = gtk_widget_get_style_context(chat->v_bt_s1);
    chat->c_v_bt_s2 = gtk_widget_get_style_context(chat->v_bt_s2);
    chat->c_v_bt_s3 = gtk_widget_get_style_context(chat->v_bt_s3);
    chat->c_v_bt_s4 = gtk_widget_get_style_context(chat->v_bt_s4);
    chat->c_v_bt_s5 = gtk_widget_get_style_context(chat->v_bt_s5);
    chat->c_v_bt_s6 = gtk_widget_get_style_context(chat->v_bt_s6);

    g_signal_connect(G_OBJECT(chat->v_bt_info), "clicked", G_CALLBACK(inf),
        chat);
    g_signal_connect(G_OBJECT(chat->v_bt_like), "clicked", G_CALLBACK(sen), (gpointer)0);
    g_signal_connect(G_OBJECT(chat->v_bt_aut), "clicked", G_CALLBACK(sen), (gpointer)1);
    g_signal_connect(G_OBJECT(chat->v_bt_s1), "clicked", G_CALLBACK(sen), (gpointer)2);
    g_signal_connect(G_OBJECT(chat->v_bt_s2), "clicked", G_CALLBACK(sen), (gpointer)3);
    g_signal_connect(G_OBJECT(chat->v_bt_s3), "clicked", G_CALLBACK(sen), (gpointer)4);
    g_signal_connect(G_OBJECT(chat->v_bt_s4), "clicked", G_CALLBACK(sen), (gpointer)5);
    g_signal_connect(G_OBJECT(chat->v_bt_s5), "clicked", G_CALLBACK(sen), (gpointer)6);
    g_signal_connect(G_OBJECT(chat->v_bt_s6), "clicked", G_CALLBACK(sen), (gpointer)7);

    gtk_container_add(GTK_CONTAINER(chat->v_scroll), chat->v_listbox);
    g_signal_connect(chat->v_window,"destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_scrolled_window_set_max_content_width ((GtkScrolledWindow *)chat->v_scroll, 500);
    gtk_window_set_title(GTK_WINDOW(chat->v_window), (const gchar *)"uchat");
    gtk_widget_show_all((GtkWidget *)chat->v_window);

   while (true)
   {
    
   }
   
}

typedef struct s_info {
    char *author;
    char *body;
    char timebuf[64];
}              t_info;

void create_row(t_info *inf, t_chat *chat);

// int auditor_watcher( t_info *inf, int k) {
//     if(k < 0) {
//         printf( "Disconnected, please restart the client\n");
//         return 0;
//     }
//     if (k == 0)
//         return 1;
//     if(!inf->author) {
//         printf("Err");
//         return 1;
//     }
//     return 2;
// }

// int *watcher_thread(t_chat *chat) {
//     // message_request_history(10);
//     while(1) {
//         t_info *inf = malloc(sizeof(t_info));
//         struct timeval tv;
//         // int k = message_receive(&tv, &inf->author, &inf->body);
//         struct tm *nowtm;

//         // if (auditor_watcher(inf, k) == 1)
//         //     continue;
//         // else if (auditor_watcher(inf, k) == 0)
//         //     break;
//         if(tv.tv_sec) {
//             nowtm = localtime(&tv.tv_sec);
//             strftime(inf->timebuf, 64, "[%d.%m.%Y %H:%M:%S]", nowtm);
//         }
//         else
//             *inf->timebuf = 0;
//         create_row(inf, chat);
//     }
//     return 0;
// }































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


typedef struct s_inf_row{
    GtkWidget *v_row;
    GtkWidget *v_vrow_box;
    GtkWidget *v_hrow;
    GtkWidget *v_body;
    GtkStyleContext *c_v_body;
}              t_inf_row;

int text_style(char i) {
    if (i == 'b')
        return 2;
    if (i == 'i')
        return 1;
    if (i == 'n')
        return 0;
    return 0;
}

int text_color(char i) {
    if (i == 'r')
        return 2;
    if (i == 'l')
        return 1;
    if (i == 'o')
        return 0;
    return 0;
}

int text_size(char i) {
    if (i == '3')
        return 2;
    if (i == '2')
        return 1;
    if (i == '1')
        return 0;
    return 1;
}

char *get_cmd(char *str);


char *parsing_cmd(char *str) {
    char *strr = get_cmd(str);
    char *strrr = strnew(3);
    int cn = 0;

    while(strr[cn] != '\0') {
        if(strr[cn] == 'b' || strr[cn] == 'i' || strr[cn] == 'n') {
            strrr[0] = strr[cn];
        }
        if (strr[cn] == 'r' || strr[cn] == 'l' || strr[cn] == 'o') {
           strrr[1] = strr[cn];
        }
        if(strr[cn] == '1' || strr[cn] == '2' || strr[cn] == '3') {
            strrr[2] = strr[cn];
        }
        cn++;
    }
    return strrr;
}

char *get_cmd(char *str) {
    int arr[300];
    int arrr[2] = {0, 0};

    arr[0] = 0;
    arr[1] = 0;
    while (str[arrr[1]] != '\0') {
        if (str[arrr[1]] == '\\') {
            arr[arrr[0]] = arrr[1];
            arrr[0]++;
        }
        arrr[1]++;
    }
    return strndup(str + arr[0], arr[1] + 1);
}

int check_on_cmd(char *str) {
    char *strr = get_cmd(str);
    if (!strcmp(strr, "\\love\\"))
        return 1;
    if (!strcmp(strr, "\\aut\\"))
        return 2;
    if (!strcmp(strr, "\\++++\\"))
        return 3;
    if (!strcmp(strr, "\\sadness\\"))
        return 4;
    if (!strcmp(strr, "\\danger\\"))
        return 5;
    if (!strcmp(strr, "\\sad_cat\\"))
        return 6;
    if (!strcmp(strr, "\\????\\"))
        return 7;
    if (!strcmp(strr, "\\hello\\"))
        return 8;
    return 0;
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

void print_text(t_row *row, t_info *inf, t_chat *chat) {
    if (check_on_cmd(inf->body) == 1)
        row->v_body = gtk_label_new(love());
    (void)chat;
}
void init_row(t_row *row, t_info *inf, t_chat *chat) {
    row->v_row = gtk_list_box_row_new();
    gtk_list_box_insert((GtkListBox *)chat->v_listbox, row->v_row, chat->v_n);
    chat->v_n++;
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



void do_print_img(t_row *row, t_info *inf, t_chat *chat, GdkPixbuf *pixbuf){
    if (check_on_cmd(inf->body) == 7)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("client/img/?.png",
            340, 340, TRUE, NULL);
    if (check_on_cmd(inf->body) == 8)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("client/img/hello.png",
            340, 340, TRUE, NULL);
    if (check_on_cmd(inf->body) == 2)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("client/img/aut.jpg",
            250, 250, TRUE, NULL);
    printf("%d\n",check_on_cmd(inf->body));
    row->v_body = gtk_image_new_from_pixbuf(pixbuf);
    (void)chat;
}

void print_img(t_row *row, t_info *inf, t_chat *chat) {
    GdkPixbuf *pixbuf;

    if (check_on_cmd(inf->body) == 3)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("client/img/+.png", 
            340, 340, TRUE, NULL);
    if (check_on_cmd(inf->body) == 4)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("client/img/sadness.png", 
            340, 340, TRUE, NULL);
    if (check_on_cmd(inf->body) == 5)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("client/img/danger.png",
            270, 270, TRUE, NULL);
    if (check_on_cmd(inf->body) == 6)
        pixbuf = gdk_pixbuf_new_from_file_at_scale ("client/img/sad_cat.png",
            390, 390, TRUE, NULL);
    do_print_img(row, inf, chat, pixbuf);
}



void print_cmd(t_row *row, t_info *inf, t_chat *chat) {
    if (check_on_cmd(inf->body) > 1)
        print_img(row, inf, chat);
    if (check_on_cmd(inf->body) == 1)
        print_text(row, inf, chat);
}
//Set Style for X
void set_class_for_X(t_row *row, t_info *inf, t_chat *chat){
    row->c_v_bt_del = gtk_widget_get_style_context(row->v_bt_del);
    gtk_style_context_add_class (row->c_v_bt_del, "X");
    (void)chat;
    (void)inf;
}
//X
typedef struct s_for_click {
    t_row *row;
    t_info *inf;
    t_chat *chat;
}              t_for_click;

void delete (GtkWidget *widget, t_for_click *c) {
        gtk_container_remove ((GtkContainer *)c->chat->v_listbox, c->row->v_row);
        (void)widget;
}

          

void print_X(t_row *row, t_info *inf, t_chat *chat) {
    if(!strcmp(inf->author, chat->login)) {
        t_for_click *c = malloc(sizeof(t_for_click));

        row->v_bt_del = gtk_button_new_with_label("X");
        gtk_widget_set_name(row->v_bt_del, "X");
        gtk_box_pack_start(GTK_BOX(row->v_hrow), 
        row->v_bt_del, FALSE, FALSE, 0);
        set_class_for_X(row, inf, chat);
        c->row = row;
        c->inf = inf;
        c->chat = chat;
        g_signal_connect(G_OBJECT(row->v_bt_del), "clicked", G_CALLBACK(delete), c);
    }
}



void set_standart_styles(t_row *row, t_info *inf, t_chat *chat) {
    gtk_style_context_add_class (row->c_v_author, "orange");
    gtk_style_context_add_class (row->c_v_time, "orange");
    gtk_style_context_add_class (row->c_v_body, "orange");
    gtk_style_context_add_class (row->c_v_author, "h2");
    gtk_style_context_add_class (row->c_v_time, "h2");
    gtk_style_context_add_class (row->c_v_body, "h2");
    gtk_style_context_add_class (row->c_v_body, "normal");
    gtk_style_context_add_class (row->c_v_time, "normal");
    gtk_style_context_add_class (row->c_v_author, "normal");
    if(!strcmp(inf->author, chat->login))
        gtk_style_context_add_class(row->c_v_bt_del, "orange");
}

void set_bold_line(t_row *row, t_info *inf, t_chat *chat) {
    gtk_style_context_remove_class (row->c_v_body, "normal");
    gtk_style_context_remove_class (row->c_v_time, "normal");
    gtk_style_context_remove_class (row->c_v_author, "normal");
    gtk_style_context_add_class (row->c_v_author, "bold");
    gtk_style_context_add_class (row->c_v_time, "bold");
    gtk_style_context_add_class (row->c_v_body, "bold");
    (void)chat;
    (void)inf;
}

void set_italic_line(t_row *row, t_info *inf, t_chat *chat) {
    gtk_style_context_remove_class (row->c_v_body, "normal");
    gtk_style_context_remove_class (row->c_v_time, "normal");
    gtk_style_context_remove_class (row->c_v_author, "normal");
    gtk_style_context_add_class (row->c_v_author, "italic");
    gtk_style_context_add_class (row->c_v_time, "italic");
    gtk_style_context_add_class (row->c_v_body, "italic");
    (void)chat;
    (void)inf;
}

void set_red_line(t_row *row, t_info *inf, t_chat *chat) {
    gtk_style_context_add_class (row->c_v_author, "red");
    gtk_style_context_add_class (row->c_v_time, "red");
    gtk_style_context_add_class (row->c_v_body, "red");
    if(!strcmp(inf->author, chat->login)) {
        gtk_style_context_add_class (row->c_v_bt_del, "red");
    }   
}

void set_lime_line(t_row *row, t_info *inf, t_chat *chat) {
    gtk_style_context_add_class (row->c_v_author, "lime");
    gtk_style_context_add_class (row->c_v_time, "lime");
    gtk_style_context_add_class (row->c_v_body, "lime");
    if(!strcmp(inf->author, chat->login)) {
        gtk_style_context_add_class (row->c_v_bt_del, "lime");
    }   
}

void set_h1_line(t_row *row, t_info *inf, t_chat *chat) {
    gtk_style_context_add_class (row->c_v_author, "h1");
    gtk_style_context_add_class (row->c_v_time, "h1");
    gtk_style_context_add_class (row->c_v_body, "h1");
    if(!strcmp(inf->author, chat->login))
        gtk_style_context_add_class (row->c_v_bt_del, "h1");
}

void set_h3_line(t_row *row, t_info *inf, t_chat *chat) {
    gtk_style_context_add_class (row->c_v_author, "h3");
    gtk_style_context_add_class (row->c_v_time, "h3");
    gtk_style_context_add_class (row->c_v_body, "h3");
    if(!strcmp(inf->author, chat->login))
        gtk_style_context_add_class (row->c_v_bt_del, "h3");
}


void set_styles(t_row *row, t_info *inf, t_chat *chat, char *str) {
    set_standart_styles(row, inf, chat);
    if (!check_on_cmd(inf->body) && inf->body[0] == '\\') {
        if (str[0] == 'b')
            set_bold_line(row, inf, chat);
        if (str[0] == 'i')
            set_italic_line(row, inf, chat);
        if (str[0] == 'n')
            set_standart_styles(row, inf, chat);
        if (str[1] == 'r')
            set_red_line(row, inf, chat);
        if (str[1] == 'l')
            set_lime_line(row, inf, chat);
        if (str[2] == '1')
            set_h1_line(row, inf, chat);
        if (str[2] == '3')
            set_h1_line(row, inf, chat);
    }
}

void set_class_for_elem(t_row *row, t_info *inf, t_chat *chat) {
    row->c_v_author = gtk_widget_get_style_context(row->v_author);
    row->c_v_time = gtk_widget_get_style_context(row->v_time);
    row->c_v_body = gtk_widget_get_style_context(row->v_body);
    gtk_style_context_add_class (row->c_v_body, "body");
    char *str = parsing_cmd(inf->body);
    
    set_styles(row, inf, chat, str);
    printf("%s\n",str);

}

void end_initing(t_row *row, t_info *inf, t_chat *chat) {
    gtk_box_pack_start(GTK_BOX(row->v_hrow), row->v_body, FALSE, FALSE, 0);
    gtk_widget_set_size_request(row->v_body,1300,30);
    if(!check_on_cmd(inf->body))
        gtk_label_set_xalign((GtkLabel *)row->v_body, 0.04);
    gtk_widget_set_size_request(row->v_body,80,30);
    print_X(row, inf, chat);
    set_class_for_elem(row, inf, chat);
}

int is_have_cmd(char *str) {
    if (str[0] == '\\' && (str[2] == '\\' || str[3] == '\\' 
        || str[4] == '\\' || str[1] == '\\'))
        return 1;
    return 0;
}

char *get_new_body_str(char *new_str) {
    int arr[2] = {0, 0};

    if(new_str[1] == '\\')
        arr[1] = 1;
    else if(new_str[2] == '\\')
        arr[1] = 2;
    else if(new_str[3] == '\\')
        arr[1] = 3;
    else if(new_str[4] == '\\')
        arr[1] = 4;
    return new_str + arr[1] + 1;
}

char *get_new_body(char *str) {
    char *new_str = strdup(str);

    if (is_have_cmd(new_str)) {
        new_str = get_new_body_str(new_str);
    }
    return new_str;
}


void create_row(t_info *inf, t_chat *chat) {   
    t_row *row = malloc(sizeof(t_row));

    init_row(row, inf, chat);
    if (check_on_cmd(inf->body)) {
        print_cmd(row, inf, chat);
    }
    else if (!check_on_cmd(inf->body)) {
        char *new_body = get_new_body(inf->body);
        row->v_body = gtk_label_new(new_body);
    }
    end_initing(row, inf, chat);
    gtk_widget_show_all(chat->v_window);
}




char *help_str(){
    char *sss = "Rules: max str len 100 chars\n"
        "Comands write only: \\cmd\\"
        "Editing: \\123\\ - font-size, \\rol\\ - color, \\inb\\ - fonts\n"
        "Stickers: \\++++\\,\n"
        "Special cmds: \\k[id]\\";
    
    return sss;
}

void set_class_for_help(t_inf_row *inf, t_chat *chat) {
    inf->c_v_body = gtk_widget_get_style_context(inf->v_body);
    gtk_style_context_add_class (inf->c_v_body, "orange");
    gtk_style_context_add_class (inf->c_v_body, "h2");
    gtk_style_context_add_class (inf->c_v_body, "normal");
    gtk_style_context_add_class (inf->c_v_body, "pading_left_100");
    (void)chat;
}

void init_help(t_inf_row *inf, t_chat *chat) {
    char *str = help_str();

    inf->v_row = gtk_list_box_row_new();
    gtk_list_box_insert((GtkListBox *)chat->v_listbox, inf->v_row, chat->v_n);
    chat->v_n++;
    inf->v_hrow = gtk_box_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(inf->v_row), inf->v_hrow);
    inf->v_body = gtk_label_new(str);
    gtk_box_pack_start(GTK_BOX(inf->v_hrow), inf->v_body, FALSE, FALSE, 0);
    gtk_widget_set_size_request(inf->v_body, 250, 10);
    gtk_label_set_xalign((GtkLabel *)inf->v_body, 0.1);
    set_class_for_help(inf, chat);
}

void inf(GtkWidget *widget, t_chat *chat) {
    (void)widget;
    t_inf_row *inf = malloc(sizeof(t_inf_row));

    init_help(inf, chat);
    gtk_widget_show_all(chat->v_window);
}





















void do_logining(GtkWidget *widget, t_s *s) {
    pthread_t loginner;
    char *login = gtk_entry_get_text(GTK_ENTRY(s->logining->username_entry));
    if(!login || !*login) {
            gtk_label_set_text(s->logining->error_label, "Something went wrong");
        return;
    }
    char *password = gtk_entry_get_text(GTK_ENTRY(s->logining->password_entry));
    if(!password || !*password) {
            gtk_label_set_text(s->logining->error_label, "Something went wrong");
        return;
    }
    
    s->logining->login = login;
    s->logining->pass = password;
    printf("%s\n", password);
    cJSON *send = cJSON_CreateObject();
    char *res;
    cJSON_AddStringToObject(send, "kind", "login");
    cJSON_AddStringToObject(send, "login", s->logining->login);
    cJSON_AddStringToObject(send, "pasword", s->logining->pass);
    res = cJSON_Print(send);
    printf("%s\n", res);
    tls_write(s->c->tls, res, strlen(res) + 1);
    while (s->c->bufc[0] != ':' && s->c->bufc[1] != 'q') {
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
            printf("Mesage (%lu): %s\n", s->c->rc, s->c->bufs);
            cJSON *msg = cJSON_Parse(s->c->bufs);
            s->logining->login_in = cJSON_GetObjectItemCaseSensitive(msg, "status")->valueint;
            s->logining->lang = cJSON_GetObjectItemCaseSensitive(msg, "lang")->valuestring;
            s->logining->theme = cJSON_GetObjectItemCaseSensitive(msg, "tema")->valuestring;

            return;
        }
        
    }
}

gboolean check_logining(t_s *s)
{
    if(s->logining->login_in) {
        //s->logining->lang = "eng" ;
        //s->logining->theme = "black";
        s->logining->login_in = 0;
        gtk_widget_hide(s->logining->window);
        init_chatt(s);
        return G_SOURCE_REMOVE;
    }
    return G_SOURCE_CONTINUE;
}

t_login *mx_client_init(t_client *c, int argc, char *argv[]){
    t_login *logining = malloc(sizeof(t_login));
    t_s *s = malloc(sizeof(t_s));

    gtk_init(&argc, &argv);
    logining->login_in = 0;
    logining->login = "";
    logining->pass = "";
    logining->ip = "";
    logining->port = "";
    logining->lang = "ENG";
    logining->theme = "BLACK";
    logining->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    logining->main_label = gtk_label_new("Uchat");
    logining->username_label = gtk_label_new("Login:");
    logining->password_label = gtk_label_new("Password:");
    logining->error_label = gtk_label_new("");
    logining->username_entry = gtk_entry_new();
    logining->password_entry = gtk_entry_new();
    logining->ok_button = gtk_button_new_with_label("Enter");
    gtk_entry_set_text(GTK_ENTRY(logining->username_entry), "admin");
    gtk_entry_set_text(GTK_ENTRY(logining->password_entry), "admin");



    logining->vbox = gtk_box_new(TRUE, 0);
    logining->main_label_box = gtk_hbox_new(TRUE, 10);
    logining->username_box = gtk_hbox_new(TRUE, 10);
    logining->password_box = gtk_hbox_new(TRUE, 10);
    logining->error_box = gtk_hbox_new(TRUE, 10);
    logining->ok_button_box = gtk_hbox_new(TRUE, 10);
    logining->cssProvider = gtk_css_provider_new();
    gtk_widget_show_all(logining->window);
    gtk_window_set_position(GTK_WINDOW(logining->window), GTK_WIN_POS_CENTER);
    gtk_entry_set_visibility(GTK_ENTRY(logining->password_entry), FALSE);
    gtk_window_set_resizable (GTK_WINDOW(logining->window), FALSE);
    gtk_css_provider_load_from_path(logining->cssProvider,
                                    "client/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(logining->cssProvider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_set_title(GTK_WINDOW(logining->window), "Uchat");
    
    g_signal_connect(G_OBJECT(logining->window), "destroy", G_CALLBACK(closeApp), NULL);
    logining->c_window = gtk_widget_get_style_context(logining->window);
    logining->c_main_label = gtk_widget_get_style_context(logining->main_label);
    logining->c_username_label = gtk_widget_get_style_context(logining->username_label);
    logining->c_password_label = gtk_widget_get_style_context(logining->password_label);
    logining->c_username_entry = gtk_widget_get_style_context(logining->username_entry);
    logining->c_password_entry = gtk_widget_get_style_context(logining->password_entry);
    logining->c_error_label = gtk_widget_get_style_context(logining->error_label);
    logining->c_ok_button = gtk_widget_get_style_context(logining->ok_button);
   

    gtk_style_context_add_class (logining->c_window, "black");
    gtk_style_context_add_class (logining->c_main_label, "black");
    gtk_style_context_add_class (logining->c_username_label, "black");
    gtk_style_context_add_class (logining->c_password_label, "black");
    gtk_style_context_add_class (logining->c_username_entry, "black");
    gtk_style_context_add_class (logining->c_password_entry, "black");
    gtk_style_context_add_class (logining->c_ok_button, "black");

    gtk_style_context_add_class (logining->c_ok_button, "ok_btn");
    gtk_style_context_add_class (logining->c_main_label, "main_label");
    gtk_style_context_add_class (logining->c_error_label, "error");



    gtk_box_pack_start(GTK_BOX(logining->main_label_box), logining->main_label, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(logining->username_box), logining->username_label, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(logining->username_box), logining->username_entry, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(logining->password_box), logining->password_label, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(logining->password_box), logining->password_entry, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(logining->error_box), logining->error_label, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(logining->ok_button_box), logining->ok_button, TRUE, TRUE, 10);

    
    gtk_box_pack_start(GTK_BOX(logining->vbox), logining->main_label_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(logining->vbox), logining->username_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(logining->vbox), logining->password_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(logining->vbox), logining->error_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(logining->vbox), logining->ok_button_box, TRUE, TRUE, 10);
    s->logining = logining;
    s->c = c;
    g_signal_connect(G_OBJECT(logining->ok_button), "clicked", G_CALLBACK(do_logining), s);
    gtk_container_add(GTK_CONTAINER(logining->window ), logining->vbox);
    g_timeout_add(50, check_logining, s);
    gtk_widget_show_all(logining->window);
    gtk_main();

    return NULL;
}





void mx_report_tls_client(t_client *c, char * host);

int init_server(t_client *c, char **argv);

int main(int argc, char **argv) {
    if (argc < 3) {
        mx_printerr("usage: uchat [ip_adress] [port]\n");
        return -1;
    }


    t_client *c = malloc(sizeof(t_client));
    if (init_server(c, argv))
        exit(1);
    mx_client_init(c, argc, argv);
    
    tls_close(c->tls);
    tls_free(c->tls);
    tls_config_free(c->config);
    printf("Closing socket...\n");
    close(c->sock);
    printf("exit client\n");
    return 0;

}


int init_server(t_client *c, char **argv) {
    c->enable = 1;


    
    if (tls_init() < 0) {
        printf("tls_init error\n");
        exit(1);
    }
    c->config = tls_config_new();
    c->tls = tls_client();
    tls_config_insecure_noverifycert(c->config);
    tls_config_insecure_noverifyname(c->config);

    if (tls_config_set_key_file(c->config, "./certificates/client.key") < 0) {
        printf("tls_config_set_key_file error\n");
        exit(1);
    }

    if (tls_config_set_cert_file(c->config, "./certificates/client.pem") < 0) {
        printf("tls_config_set_cert_file error\n");
        exit(1);
    }

    tls_configure(c->tls, c->config);

    memset(&c->hints, 0, sizeof(c->hints));
    c->hints.ai_socktype = SOCK_STREAM;
    if ((c->err = getaddrinfo(argv[1], argv[2], &c->hints, &c->peer_address)) != 0) {
        fprintf(stderr, "getaddrinfo() failed. (%s)\n", gai_strerror(c->err));
        return 1;
    }
    printf("Remote address is: ");
    
    getnameinfo(c->peer_address->ai_addr, c->peer_address->ai_addrlen,
                c->address_buffer, sizeof(c->address_buffer),
                c->service_buffer, sizeof(c->service_buffer),
                NI_NUMERICHOST);
    printf("%s %s\n", c->address_buffer, c->service_buffer);

    c->sock = socket(c->peer_address->ai_family,
                  c->peer_address->ai_socktype, c->peer_address->ai_protocol);
    if (c->sock == -1) {
        printf("error sock = %s\n", strerror(errno));
        return 1;
    }
    setsockopt(c->sock, IPPROTO_TCP, SO_KEEPALIVE, &c->enable, sizeof(int));
    if (connect(c->sock, c->peer_address->ai_addr, c->peer_address->ai_addrlen)) {
        printf("connect error = %s\n", strerror(errno));
        return 1;
    }
    freeaddrinfo(c->peer_address);
    printf("connect TCP sock =%d\n", c->sock);

    if (tls_connect_socket(c->tls, c->sock, "uchat_server") < 0) {
        printf("tls_connect error\n");
        printf("%s\n", tls_error(c->tls));
        exit(1);
    }
    printf("tls connect +\n");
    if (tls_handshake(c->tls) < 0) {
        printf("tls_handshake error\n");
        printf("%s\n", tls_error(c->tls));
        exit(1);
    }
    mx_report_tls_client(c, "client");
    printf("\n");
    // tls_write(c->tls, "TLS connect", strlen("TLS connect"));
    
    c->rc = 0;

    c->pfd[0].fd = 0;
    c->pfd[0].events = POLLIN;
    c->pfd[1].fd = c->sock;
    c->pfd[1].events = POLLIN;
    return 0;
}

void mx_report_tls_client(t_client *c, char * host) {
    time_t t;
    const char *ocsp_url;

    fprintf(stderr, "\nTLS handshake negotiated %s/%s with host %s\n",
            tls_conn_version(c->tls), tls_conn_cipher(c->tls), host);
    fprintf(stderr, "Peer name: %s\n", host);
    if (tls_peer_cert_subject(c->tls))
        fprintf(stderr, "Subject: %s\n",
                tls_peer_cert_subject(c->tls));
    if (tls_peer_cert_issuer(c->tls))
        fprintf(stderr, "Issuer: %s\n",
                tls_peer_cert_issuer(c->tls));
    if ((t = tls_peer_cert_notbefore(c->tls)) != -1)
        fprintf(stderr, "Valid From: %s", ctime(&t));
    if ((t = tls_peer_cert_notafter(c->tls)) != -1)
        fprintf(stderr, "Valid Until: %s", ctime(&t));
    if (tls_peer_cert_hash(c->tls))
        fprintf(stderr, "Cert Hash: %s\n",
                tls_peer_cert_hash(c->tls));
    ocsp_url = tls_peer_ocsp_url(c->tls);
    if (ocsp_url != NULL)
        fprintf(stderr, "OCSP URL: %s\n", ocsp_url);
    switch (tls_peer_ocsp_response_status(c->tls)) {
        case TLS_OCSP_RESPONSE_SUCCESSFUL:
            fprintf(stderr, "OCSP Stapling: %s\n",
                    tls_peer_ocsp_result(c->tls) == NULL ?  "" :
                    tls_peer_ocsp_result(c->tls));
            fprintf(stderr,
                    "  response_status=%d cert_status=%d crl_reason=%d\n",
                    tls_peer_ocsp_response_status(c->tls),
                    tls_peer_ocsp_cert_status(c->tls),
                    tls_peer_ocsp_crl_reason(c->tls));
            t = tls_peer_ocsp_this_update(c->tls);
            fprintf(stderr, "  this update: %s",
                    t != -1 ? ctime(&t) : "\n");
            t =  tls_peer_ocsp_next_update(c->tls);
            fprintf(stderr, "  next update: %s",
                    t != -1 ? ctime(&t) : "\n");
            t =  tls_peer_ocsp_revocation_time(c->tls);
            fprintf(stderr, "  revocation: %s",
                    t != -1 ? ctime(&t) : "\n");
            break;
        case -1:
            break;
        default:
            fprintf(stderr, "OCSP Stapling:  failure - response_status %d (%s)\n",
                    tls_peer_ocsp_response_status(c->tls),
                    tls_peer_ocsp_result(c->tls) == NULL ?  "" :
                    tls_peer_ocsp_result(c->tls));
            break;

    }
}
