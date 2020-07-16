#include "client.h"


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

int mx_exit_chat(t_s *s) {
    tls_close(s->c->tls);
    tls_free(s->c->tls);
    tls_config_free(s->c->cnf);
    printf("Closing socket...\n");
    close(s->c->sock);
    printf("exit client\n");
    return 0;
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




void mx_first_serv_init(t_s *s) {
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

int mx_second_serv_init(t_s *s, char **argv) {
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

int mx_third_serv_init(t_s *s) {
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

int mx_init_server(t_s *s, char **argv) {
    mx_first_serv_init(s);
    if (mx_second_serv_init(s, argv))
        return 1;
    if (mx_third_serv_init(s))
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

char *mx_help_str_eng() {
    char *sss = "Rules: max str len 100 chars\n"
        "Comands write only: |cmd|\n"
        "Formatin: |12| - font-size, |rol| - color, |ib| - fonts\n"
        "Stickers: |love|, |beuty|, |++++|, |sadness|, |danger|, |sad_cat|, "
        "|????|, |hello|, you can write this\n"
        "If you are admin you can kick users: |k_user|\n"
        "Change password: |p_new_pass|, password can`t be longer 30 chars\n"
        "Message editing: |e1234567890|new_mess\n"
        "On click Delete you are drop your account\n"
        "|m| on/off anti mat system\n"
        "|v| && |s| notification visual/sound off/on\n"
        "|c| clear history for admin\n"
        "|x_user| privat message\n";
    return sss;
}

char *mx_help_str_rus() {
    char *sss = "Правила: максимум 100 символов \n"
        "Команды только для записи: | cmd | \n"
        "Formatin: |12| - размер шрифта, |rol| - цвет, |ib| - шрифты \n"
        "Наклейки: |love|, |beuty|, |++++|, |sadness|, |danger|, |sad_cat|, "
        "|????|, |hello|, you can write this\n"
        "Если вы являетесь администратором, "
        "вы можете кикнуть пользователей: |k_user| \n"
        "Изменить пароль: |p_new_pass|, пароль не может быть длиннее"
        "30 символов \n"
        "Редактирование сообщения: |е1234567890| new_mess \n"
        "После нажатия кнопки Удалить вы удаляете свой аккаунт \n"
        "|m| вкл/выкл анти мат системы \n"
        "|v| && |s| уведомление визуально/звук выключен/включен \n"
        "|c| очистить историю для администратора \n"
        "|x_user| приватное сообщение \n";
    return sss;
}

char *mx_help_str(t_s *s) {
    if (!strcmp(s->h->lang, "eng"))
        return mx_help_str_eng();
    if (!strcmp(s->h->lang, "rus"))
        return mx_help_str_rus();
    return mx_help_str_eng();        
}


int mx_is_digit_for_editing(char *m, int i[2]) {
    char sss[1000];
    sprintf(sss ,"%s\n", strndup(m+2, i[1] - 2));

    for (unsigned long hh = 0; hh < strlen(sss) - 1; hh++) {
        if (!mx_isdigit(sss[hh]))
            return 0;
    }
    return 1;
}

int mx_is_have_editing(char *m) {
    int i[2] = {0, 0};

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|') {
                i[1] = gg;
                break;
            }
            if (m[gg] == '\0')
                return 0;
        }
        if (m[1] == 'e') {
            return mx_is_digit_for_editing(m, i);
        }
    }
    return 0;
}


int mx_get_editing_id(char *m) {
    int i[2] = {0, 0};
    char sss[1000];
    int cc;

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|')
                i[1] = gg;
        }
    }
    sprintf(sss ,"%s\n", strndup(m+2, i[1] - 2));
    cc = atoi(sss);
    return cc;
}

char *mx_strneww(int size) {
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}

char *mx_get_new_body_e(char *m) {
    int i[2] = {0, 0};
    char *sss = mx_strneww(1000);

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|') {
                i[1] = gg;
                break;
            } 
        }
    }
    sprintf(sss ,"%s", strndup(m + i[1] + 1, strlen(m) - i[1] - 1));
    return sss;
}




char *mx_edit_creating(char *m, t_s *s) {
    cJSON *send = cJSON_CreateObject();
    int id_edit_mess = mx_get_editing_id(m);
    char *new_body = mx_get_new_body_e(m);
    
    cJSON_AddStringToObject(send, "kind", "edit");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "msg", new_body);
    cJSON_AddNumberToObject(send, "edit_id", id_edit_mess);
    return cJSON_Print(send);
}

int mx_is_have_drop(char *m) {
    int i[2] = {0, 0};

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|')
                i[1] = gg;
            if (m[gg] == '\0')
                return 0;
        }
        if (strlen(m) > 4)
            if (m[1] == 'k' &&  m[2] == '_') {
                return 1;
            }
    }
    return 0;
}

char *mx_get_user_drop(char *m) {
    int i[2] = {0, 0};
    char *sss = mx_strneww(1000);

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|') {
                i[1] = gg;
                break;
            }
        }
    }
    sprintf(sss, "%s", strndup(m + 3, i[1] - 3));
    return sss;
}

char *mx_drop_creating(char *m, t_s *s) {
    cJSON *send = cJSON_CreateObject();
    char *user_drop = mx_get_user_drop(m);
    
    cJSON_AddStringToObject(send, "kind", "drop_user");
    cJSON_AddStringToObject(send, "admin", s->h->login);
    cJSON_AddStringToObject(send, "drop_user", user_drop);
    return cJSON_Print(send);
}

int mx_is_have_change_pass(char *m) {
    int i[2] = {0, 0};

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|') {
                i[1] = gg;
                break;
            }
            if (m[gg] == '\0')
                return 0;
        }
        if (strlen(m) > 4)
            if (m[1] == 'p' &&  m[2] == '_') {
                return 1;
            }
    }
    return 0;
}

char *mx_get_new_pass(char *m) {
    int i[2] = {0, 0};
    char *sss = mx_strneww(1000);

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|') {
                i[1] = gg;
                break;
            }
        }
    }
    sprintf(sss, "%s", strndup(m + 3, i[1] - 3));
    return sss;
}



char *mx_change_pass_creating(char *m, t_s *s) {
    cJSON *send = cJSON_CreateObject();
    char *new_pass = mx_get_new_pass(m);
    if (strlen(new_pass) > 30) {
        cJSON_AddStringToObject(send, "kind", "new_password");
        cJSON_AddStringToObject(send, "who_change", s->h->login);
        cJSON_AddStringToObject(send, "new_pass", new_pass);
    }
    return cJSON_Print(send);
}

int mx_is_have_matyki(char *m, t_s *s) {
    if (strlen(m) == 3) {
        if (m[0] == '|' && m[1] == 'm' && m[2] == '|') {
            if (s->h->is_output_matyki)
                s->h->is_output_matyki = 0;
            else 
                s->h->is_output_matyki = 1;
            return 1;
        }
        return 0;
    }
    return 0;
}

int mx_is_have_sound(char *m, t_s *s) {
    if (strlen(m) == 3) {
        if (m[0] == '|' && m[1] == 's' && m[2] == '|') {
            if (s->h->is_output_sound)
                s->h->is_output_sound = 0;
            else 
                s->h->is_output_sound = 1;
            return 1;
        }
        return 0;
    }
    return 0;
}

int mx_is_have_visual(char *m, t_s *s) {
    if (strlen(m) == 3) {
        if (m[0] == '|' && m[1] == 'v' && m[2] == '|') {
            if (s->h->is_output_visual)
                s->h->is_output_visual = 0;
            else 
                s->h->is_output_visual = 1;
            return 1;
        }
        return 0;
    }
    return 0;
}


int mx_is_have_clean_history(char *m) {
    if (strlen(m) == 3) {
        if (m[0] == '|' && m[1] == 'c' && m[2] == '|') {
            return 1;
        }
        return 0;
    }
    return 0;
}

char *mx_clean_history( t_s *s) {
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "clean_chat");
    cJSON_AddStringToObject(send, "who_clean", s->h->login);
    return cJSON_Print(send);
}

char *mx_parsing_normal_mess(char *m, t_s *s) {
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "msg");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "msg", m);
    return cJSON_Print(send);
}


int mx_is_have_privat_message(char *m) {
    int i[2] = {0, 0};

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|')
                i[1] = gg;
            if (m[gg] == '\0')
                return 0;
        }
        if (strlen(m) > 4)
            if (m[1] == 'x' &&  m[2] == '_') {
                return 1;
            }
    }
    return 0;
}

char *mx_get_user_for_privat(char *m) {
    int i[2] = {0, 0};
    char *sss = mx_strneww(1000);

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|') {
                i[1] = gg;
                break;
            }
        }
    }
    sprintf(sss, "%s", strndup(m + 3, i[1] - 3));
    return sss;
}






char *mx_create_privat_message(char *m, t_s *s) {
    cJSON *send = cJSON_CreateObject();
    char *user_for_privat = mx_get_user_for_privat(m);
    char *msg = mx_get_new_body_e(m);
    
    cJSON_AddStringToObject(send, "kind", "privat_mess");
    cJSON_AddStringToObject(send, "who_send", s->h->login);
    cJSON_AddStringToObject(send, "to_user", user_for_privat);
    cJSON_AddStringToObject(send, "msg", msg);
    return cJSON_Print(send);
}

char *mx_parsing_mes(char *m, t_s *s) {
    if (mx_is_have_editing(m))
        return mx_edit_creating(m, s);
    else if (mx_is_have_drop(m))
        return mx_drop_creating(m, s);
    else if (mx_is_have_change_pass(m))
        return mx_change_pass_creating(m, s);
    else if (mx_is_have_matyki(m, s))
        return NULL;
    else if (mx_is_have_sound(m, s))
        return NULL;
    else if (mx_is_have_visual(m, s))
        return NULL;
    else if (mx_is_have_visual(m, s))
        return NULL;
    else if (mx_is_have_clean_history(m))
        return mx_clean_history(s);
    else if (mx_is_have_privat_message(m))
        return mx_create_privat_message(m, s);
    return mx_parsing_normal_mess(m, s);
}



void mx_do_s(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = (char *)gtk_entry_get_text(GTK_ENTRY(s->h->v_main_e));
    
        if (!message || !*message )
            return;
        if (strlen(message) < 110 && strlen(message) > 0) {
            char *res = mx_parsing_mes(message, s);
            if (res != NULL)
                tls_write(s->c->tls, res, strlen(res) + 1);
        }
        else
            printf("\n");
        gtk_entry_set_text(GTK_ENTRY(s->h->v_main_e), "");
    }
    (void)widget;
}

void mx_drop_sesion(t_s *s) {
    cJSON *send = cJSON_CreateObject();
    char *res;

    cJSON_AddStringToObject(send, "kind", "drop_sesion");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddNumberToObject(send, "drop_id", s->h->was_connect);
    res = cJSON_Print(send);
    tls_write(s->c->tls, res, strlen(res) + 1);
}

void mx_set_class_for_help(t_inf_row *inf) {
    inf->c_v_body = gtk_widget_get_style_context(inf->v_body);
    gtk_style_context_add_class(inf->c_v_body, "pading_left_100");
}

void init_help(t_inf_row *inf, t_s *s) {
    char *str = mx_help_str(s);

    inf->v_row = gtk_list_box_row_new();
    gtk_list_box_insert((GtkListBox *)s->h->v_listbox, inf->v_row, s->h->v_n);
    s->h->v_n++;
    inf->v_hrow = gtk_box_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(inf->v_row), inf->v_hrow);
    inf->v_body = gtk_label_new(str);
    gtk_box_pack_start(GTK_BOX(inf->v_hrow), inf->v_body, FALSE, FALSE, 0);
    gtk_widget_set_size_request(inf->v_body, 250, 10);
    gtk_label_set_xalign((GtkLabel *)inf->v_body, 0.1);
    mx_set_class_for_help(inf);
}

int mx_show_widget(GtkWidget *widget) {
    gtk_widget_show_all(widget);
    return 0;
}

void mx_inf(GtkWidget *widget, t_s *s) {
    (void)widget;
    t_inf_row *inf = malloc(sizeof(t_inf_row));

    init_help(inf, s);
    g_idle_add ((int (*)(void *))mx_show_widget, s->h->v_window);
}



void mx_closeApp(GtkWidget *window, t_s *s) {   
    (void)window;
    mx_exit_chat(s);
    printf("Destroy\n");
    gtk_main_quit();
}

void mx_closeApp2(GtkWidget *window, t_s *s) { 
    mx_drop_sesion(s);
    mx_closeApp(window, s);
}


char *mx_get_cmd(char *str) {
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

int mx_check_on_cmd(char *str) {
    char *strr = mx_get_cmd(str);
    if (!strcmp(strr, "|love|"))
        return 1;
    if (!strcmp(strr, "|beuty|"))
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






char *mx_what_return(int gg) {
    if (gg == 0)
        return "|love|";
    if (gg == 1)
        return "|beuty|";
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

void mx_sen0(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = mx_what_return(0);
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

void mx_sen1(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = mx_what_return(1);
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

void mx_sen2(GtkWidget *widget, t_s *s) {
    if (s->h->can_do_msg) {
        s->h->can_do_msg = 0;
        char *message = mx_what_return(2);
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



void mx_init_row(t_row *row, t_info *inf, t_s *s) {
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


void mx_delete(GtkWidget *widget, t_for_click *c) {
    if (c->s->h->can_do_msg) {
        cJSON *send = cJSON_CreateObject();
        cJSON_AddStringToObject(send, "kind", "delete");
        cJSON_AddStringToObject(send, "login", c->s->h->login);
        cJSON_AddNumberToObject(send, "id", c->inf->id);
        char *res = cJSON_Print(send);
        c->s->h->can_do_msg = 0;
        tls_write(c->s->c->tls, res, strlen(res) + 1);
    }
    (void)widget;
}

void mx_set_class_for_X(t_row *row, t_info *inf, t_s *s) {
    row->c_v_bt_del = gtk_widget_get_style_context(row->v_bt_del);
    gtk_style_context_add_class(row->c_v_bt_del, "X");
    (void)inf;
    (void)s;
}

gboolean mx_check_editing(t_for_click *c) {  
    if (c->s->h->d_id == c->inf->id || c->s->h->is_drop_all_messages) {
        gtk_container_remove((GtkContainer *)c->s->h->v_listbox,
            c->row->v_row);
        c->s->h->d_id = -2;
        return G_SOURCE_REMOVE;
    }
    if (c->s->h->e_id == c->inf->id && c->row->is_sticker) {
        gtk_label_set_text((GtkLabel *)c->row->v_body, c->s->h->edit_txt);
        return G_SOURCE_CONTINUE;
    }
    return G_SOURCE_CONTINUE;
}

void mx_print_X(t_row *row, t_info *inf, t_s *s) {
    t_for_click *c = malloc(sizeof(t_for_click));

    c->row = row;
    c->inf = inf;
    c->s = s;
    if (!strcmp(inf->author, s->h->login)) {
        row->v_bt_del = gtk_button_new_with_label("X");
        gtk_widget_set_name(row->v_bt_del, "X");
        gtk_box_pack_start(GTK_BOX(row->v_hrow), 
        row->v_bt_del, FALSE, FALSE, 0);
        mx_set_class_for_X(row, inf, s);
        g_signal_connect(G_OBJECT(row->v_bt_del), "clicked",
            G_CALLBACK(mx_delete), c);
    }   
    g_timeout_add(10, (GSourceFunc)mx_check_editing, c);
}

void mx_edit(GtkWidget *widget, t_for_click *c) {
    char mes[500];
    sprintf(mes, "|e%d|", c->inf->id);

    gtk_entry_set_text(GTK_ENTRY(c->s->h->v_main_e), mes);
    (void)widget;
}

void mx_print_E(t_row *row, t_info *inf, t_s *s) {
    t_for_click *c = malloc(sizeof(t_for_click));

    c->row = row;
    c->inf = inf;
    c->s = s;
    if (!strcmp(inf->author, s->h->login) && row->is_sticker) {
        row->v_bt_ed = gtk_button_new_with_label("E");
        gtk_box_pack_start(GTK_BOX(row->v_hrow), 
        row->v_bt_ed, FALSE, FALSE, 0);
        row->c_v_bt_ed = gtk_widget_get_style_context(row->v_bt_ed);
        gtk_style_context_add_class(row->c_v_bt_ed, "X");
        g_signal_connect(G_OBJECT(row->v_bt_ed), "clicked",
                         G_CALLBACK(mx_edit), c);
    }
}

void mx_set_bold_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "bold");
    gtk_style_context_add_class (row->c_v_time, "bold");
    gtk_style_context_add_class (row->c_v_body, "bold");
}

void mx_set_italic_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "italic");
    gtk_style_context_add_class (row->c_v_time, "italic");
    gtk_style_context_add_class (row->c_v_body, "italic");
}


void mx_set_red_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "red");
    gtk_style_context_add_class (row->c_v_time, "red");
    gtk_style_context_add_class (row->c_v_body, "red");   
}

void mx_set_lime_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "lime");
    gtk_style_context_add_class (row->c_v_time, "lime");
    gtk_style_context_add_class (row->c_v_body, "lime"); 
}

void mx_set_orange_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "orange");
    gtk_style_context_add_class (row->c_v_time, "orange");
    gtk_style_context_add_class (row->c_v_body, "orange"); 
}

void mx_set_h1_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "h1");
    gtk_style_context_add_class (row->c_v_time, "h1");
    gtk_style_context_add_class (row->c_v_body, "h1");
}

void mx_set_h2_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "h2");
    gtk_style_context_add_class (row->c_v_time, "h2");
    gtk_style_context_add_class (row->c_v_body, "h2");
}

void mx_set_styles_for_mess(t_row *row, char *str, t_info *inf) {
    if (!mx_check_on_cmd(inf->body) && inf->body[0] == '|') {
        if (str[0] == 'b')
            mx_set_bold_line(row);
        if (str[0] == 'i')
            mx_set_italic_line(row);
        if (str[1] == 'r')
            mx_set_red_line(row);
        if (str[1] == 'l')
            mx_set_lime_line(row);
        if (str[1] == 'o')
            mx_set_orange_line(row);
        if (str[2] == '1')
            mx_set_h1_line(row);
        if (str[2] == '2')
            mx_set_h2_line(row);
    }
}




char *mx_parsing_cmd(char *str) {
    char *strr = mx_get_cmd(str);
    char *strrr = mx_strneww(3);
    int cn = 0;

    while(strr[cn] != '\0') {
        if (strr[cn] == 'b' || strr[cn] == 'i' ) {
            strrr[0] = strr[cn];
        }
        if (strr[cn] == 'r' || strr[cn] == 'l' || strr[cn] == 'o') {
           strrr[1] = strr[cn];
        }
        if (strr[cn] == '1' || strr[cn] == '2' ) {
            strrr[2] = strr[cn];
        }
        cn++;
    }
    return strrr;
}

void mx_set_class_for_elem(t_row *row, t_info *inf) {
    row->c_v_author = gtk_widget_get_style_context(row->v_author);
    row->c_v_time = gtk_widget_get_style_context(row->v_time);
    row->c_v_body = gtk_widget_get_style_context(row->v_body);
    char *str = mx_parsing_cmd(inf->body);
    
    mx_set_styles_for_mess(row, str, inf);
}

void mx_end_initing(t_row *row, t_info *inf, t_s *s) {
    gtk_box_pack_start(GTK_BOX(row->v_hrow), row->v_body, FALSE, FALSE, 0);
    gtk_widget_set_size_request(row->v_body,100,30);    
    gtk_widget_set_size_request(row->v_body,80,30);
    mx_print_X(row, inf, s);
    mx_print_E(row, inf, s);
    mx_set_class_for_elem(row, inf);
    (void)inf;
    (void)s;
}

void mx_do_print_img(t_row *row, t_info *inf, GdkPixbuf *px) {
    if (mx_check_on_cmd(inf->body) == 7)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/?.png",
            340, 340, TRUE, NULL);
    if (mx_check_on_cmd(inf->body) == 8)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/hello.png",
            340, 340, TRUE, NULL);
    if (mx_check_on_cmd(inf->body) == 2)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/aut.jpg",
            250, 250, TRUE, NULL);
    row->v_body = gtk_image_new_from_pixbuf(px);
}

void mx_print_img(t_row *row, t_info *inf) {
    GdkPixbuf *px;

    if (mx_check_on_cmd(inf->body) == 3)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/+.png",
            340, 340, TRUE, NULL);
    if (mx_check_on_cmd(inf->body) == 4)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/sadness.png",
            340, 340, TRUE, NULL);
    if (mx_check_on_cmd(inf->body) == 5)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/danger.png",
            270, 270, TRUE, NULL);
    if (mx_check_on_cmd(inf->body) == 6)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/sad_cat.png",
            390, 390, TRUE, NULL);
    mx_do_print_img(row, inf, px);
}


char *mx_love() {
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

void mx_print_text(t_row *row, t_info *inf) {
    if (mx_check_on_cmd(inf->body) == 1)
        row->v_body = gtk_label_new(mx_love());
}

void mx_print_cmd(t_row *row, t_info *inf) {
    if (mx_check_on_cmd(inf->body) > 1)
        mx_print_img(row, inf);
    if (mx_check_on_cmd(inf->body) == 1)
        mx_print_text(row, inf);
}

char *mx_get_new_body_str(char *new_str) {
    int arr[2] = {0, 0};

    if (new_str[1] == '|')
        arr[1] = 1;
    else if (new_str[2] == '|')
        arr[1] = 2;
    else if (new_str[3] == '|')
        arr[1] = 3;
    else if (new_str[4] == '|')
        arr[1] = 4;
    return new_str + arr[1] + 1;
}

int mx_is_have_cmd(char *str) {
    if (str[0] == '|' && (str[2] == '|' || str[3] == '|' 
        || str[4] == '|' || str[1] == '|'))
        return 1;
    return 0;
}

int mx_arr_size(char **arr) {
    int result = 0;

    while (*arr) {
        result++;
        arr++;
    }
    return result;
}

char *mx_strncat(char *restrict s1, const char *restrict s2, size_t n) {
    char *save = s1;

    s1 += mx_strlen(s1);
    mx_strncpy(s1, s2, n);
    return save;
}




char *mx_replace_sub(const char *str, const char *sub,
                     const char *replace) {
    int subs = mx_count_substr(str, sub);
    int subs_length = mx_strlen(sub) * subs;
    int replace_length = mx_strlen(replace) * subs;
    char *result = NULL;
    int index = 0;

    if (!*str || !*sub) {
        return NULL;
    }
    result = mx_strnew(mx_strlen(str) - subs_length + replace_length);
    while ((index = mx_get_substr_index(str, sub)) != -1) {
        mx_strncat(result, str, index);
        mx_strcat(result, replace);
        str += index + mx_strlen(sub);
    }
    mx_strcat(result, str);
    return result;
}

char *mx_get_without_mats(char *new_str) {
    char *arr_eng_mats[1024] = {"fuck", "dick", "suck", "shut", "cocks", 
        "condom", "fart", "pussy", "ass", "bitch", "shit"};
    char *arr_rus_mats[1024] = {"хуй", "гавно", "лох", "сука", "пососи",
        "ретард", "pidor", "гамосек", "сосунок", "даун", "аутист", "блядь",
        "ебать", "тупо", "шлюха", "деби", "гей", "отбитый", "конча"};

    for (int i = 0; i < mx_arr_size(arr_eng_mats); i++) {
        new_str = mx_replace_sub(new_str, arr_eng_mats[i], "***");
    }
    for (int i = 0; i < mx_arr_size(arr_rus_mats); i++) {
        new_str = mx_replace_sub(new_str, arr_rus_mats[i], "***");
    }
    sprintf(new_str, "%s", new_str);
    return new_str;
}

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

void mx_delete_msg(t_s *s, cJSON *msg) {
    s->h->d_id = cJSON_GetObjectItemCaseSensitive(msg, "id")->valueint;
}

void mx_edit_mess(t_s *s, cJSON *msg) {
    s->h->e_id = cJSON_GetObjectItemCaseSensitive(msg, "id")->valueint;
    s->h->edit_txt = cJSON_GetObjectItemCaseSensitive(msg, "msg")->valuestring;
}

void mx_init_connect_msg(t_s *s, cJSON *msg) {
    s->h->was_connect = cJSON_GetObjectItemCaseSensitive(msg,
        "conn_id")->valueint;
}

void mx_drop_acc(GtkWidget *widget, t_s *s) {
    (void)widget;
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "drop_acc");
    cJSON_AddStringToObject(send, "login", s->h->login);
    char *res = cJSON_Print(send);

    tls_write(s->c->tls, res, strlen(res) + 1);
    mx_closeApp2(s->h->v_window, s);
}



void mx_droping_account(t_s *s, cJSON *msg) {
    s->h->drop_acc = cJSON_GetObjectItemCaseSensitive(msg, "drop_user")->valuestring;

    if (!strcmp(s->h->drop_acc, s->h->login))
        mx_drop_acc(NULL, s);
}

gboolean mx_set_cant_delete_all_mes(t_s *s) {
    s->h->is_drop_all_messages = 0;
    return G_SOURCE_REMOVE;
}

void mx_drop_all_messages(t_s *s) {
    s->h->is_drop_all_messages = 1;
    g_timeout_add(2000, (GSourceFunc)mx_set_cant_delete_all_mes, s);
}

char *mx_create_privat_message_body(cJSON *msg) {
    char *sss = mx_strneww(1024);
    char *who_send = cJSON_GetObjectItemCaseSensitive(msg, "who_send")->valuestring;
    char *msgg = cJSON_GetObjectItemCaseSensitive(msg, "msg")->valuestring;

    sprintf(sss, "%s: %s", who_send, msgg);
    return sss;
}

void mx_create_privat_mes(t_s *s, cJSON *msg) {
    char *who_get = cJSON_GetObjectItemCaseSensitive(msg, "to_user")->valuestring;

    if(!strcmp(who_get, s->h->login)) {
        t_inf_row *inf = malloc(sizeof(t_inf_row));
        char *str = mx_create_privat_message_body(msg);

        inf->v_row = gtk_list_box_row_new();
        gtk_list_box_insert((GtkListBox *)s->h->v_listbox, inf->v_row, s->h->v_n);
        s->h->v_n++;
        inf->v_hrow = gtk_box_new(FALSE, 0);
        gtk_container_add(GTK_CONTAINER(inf->v_row), inf->v_hrow);
        inf->v_body = gtk_label_new(str);
        gtk_box_pack_start(GTK_BOX(inf->v_hrow), inf->v_body, FALSE, FALSE, 0);
        gtk_widget_set_size_request(inf->v_body, 250, 50);
        gtk_label_set_xalign((GtkLabel *)inf->v_body, 0.1);
        mx_set_class_for_help(inf);
    }
    g_idle_add ((int (*)(void *))mx_show_widget, s->h->v_window);
}

void mx_check_mesage_from_serv(t_s *s, cJSON *msg) {
    char *ch = cJSON_GetObjectItemCaseSensitive(msg, "kind")->valuestring;

    if (!strcmp(ch, "msg"))
        mx_create_msg(s, msg);
    if (!strcmp(ch, "delete"))
        mx_delete_msg(s, msg);
    if (!strcmp(ch, "connection"))
        mx_init_connect_msg(s, msg);
    if (!strcmp(ch, "drop_user"))
        mx_droping_account(s, msg);
    if (!strcmp(ch, "edit"))
        mx_edit_mess(s, msg);
    if (!strcmp(ch, "drop_all_mess"))
        mx_drop_all_messages(s);
    if (!strcmp(ch, "privat_mess"))
        mx_create_privat_mes(s, msg);
}

void mx_can_deleting_set(t_s *s) {
    s->h->can_do_msg = 1;
}

void mx_watcher_thread(t_s *s) {
    s->h->can_do_msg = 1;
    g_timeout_add(3000, (GSourceFunc)mx_can_deleting_set, s);
    while (true) {
        bzero(s->c->bufs, 1000);
        poll(s->c->pfd, 2, -1);
        if (s->c->pfd[1].revents & POLLIN) {
            if ((s->c->rc = tls_read(s->c->tls, s->c->bufs, 1000)) <= 0) 
                break;
            cJSON *msg = cJSON_Parse(s->c->bufs);
            printf("%s\n", s->c->bufs);
            mx_check_mesage_from_serv(s, msg);
        }
    }
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


void mx_1_chat_init(t_s *s) {
    s->h->login = s->l->login;
    s->h->lang = s->l->lang;
    s->h->v_n = 0;
    s->h->theme = s->l->theme;
    mx_create_content(s);
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
    g_signal_connect(G_OBJECT(s->h->v_bt_e), "clicked", G_CALLBACK(mx_do_s), s);
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


void mx_set_styles(t_s *s) {
    if (!strcmp(s->h->theme, "black")) {
        mx_set_black(s);
        mx_set_standart_style(s);
        return;
    }
    if (!strcmp(s->h->theme, "white")) {
        mx_set_white(s);
        mx_set_standart_style(s);
        return;
    }
    mx_set_black(s);
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


void mx_set_b(GtkWidget *widget, t_s *s) {
    (void)widget;
    mx_set_black(s);
    
}
void mx_set_w(GtkWidget *widget, t_s *s) {
    (void)widget;
    mx_set_white(s);
}

void mx_set_engl(t_s *s) {
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

void mx_set_russ(t_s *s) {
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

void mx_set_en(GtkWidget *widget, t_s *s) {
    (void)widget;
    mx_set_engl(s);
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "ui");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "tema", s->h->theme);
    cJSON_AddStringToObject(send, "lang", "eng");
    char *res = cJSON_Print(send);

    tls_write(s->c->tls, res, strlen(res) + 1);
}

void mx_set_ru(GtkWidget *widget, t_s *s) {
    (void)widget;
    mx_set_russ(s);
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "ui");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "tema", s->h->theme);
    cJSON_AddStringToObject(send, "lang", "rus");
    char *res = cJSON_Print(send);

    tls_write(s->c->tls, res, strlen(res) + 1);
}

void mx_5_chat_init(t_s *s) {
    s->h->d_id = -2;
    s->h->is_output_matyki = 0;
    s->h->is_output_sound = 1;
    s->h->is_output_visual = 0;
    s->h->is_drop_all_messages = 0;
    g_signal_connect(G_OBJECT(s->h->v_l_btn_en), "clicked", 
        G_CALLBACK(mx_set_en), s);
    g_signal_connect(G_OBJECT(s->h->v_l_btn_ru), "clicked",
        G_CALLBACK(mx_set_ru), s);
    g_signal_connect(G_OBJECT(s->h->v_t_btn_b), "clicked",
        G_CALLBACK(mx_set_b), s);
    g_signal_connect(G_OBJECT(s->h->v_t_btn_w), "clicked", 
        G_CALLBACK(mx_set_w), s);
    g_signal_connect(G_OBJECT(s->h->v_l_btn_rm), "clicked", 
        G_CALLBACK(mx_drop_acc), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_inf), "clicked", 
        G_CALLBACK(mx_inf), s);
}

void mx_6_chat_init(t_s *s) {
    g_signal_connect(G_OBJECT(s->h->v_bt_lik), "clicked", 
        G_CALLBACK(mx_sen0), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_aut), "clicked", 
        G_CALLBACK(mx_sen1), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_s1), "clicked", 
        G_CALLBACK(mx_sen2), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_s2), "clicked",
        G_CALLBACK(mx_sen3), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_s3), "clicked", 
        G_CALLBACK(mx_sen4), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_s4), "clicked",
        G_CALLBACK(mx_sen5), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_s5), "clicked",
        G_CALLBACK(mx_sen6), s);
    g_signal_connect(G_OBJECT(s->h->v_bt_s6), "clicked",
        G_CALLBACK(mx_sen7), s);
}

void mx_7_chat_init(t_s *s) {
    gtk_container_add(GTK_CONTAINER(s->h->v_scroll), s->h->v_listbox);
    g_signal_connect(s->h->v_window,"destroy",G_CALLBACK(mx_closeApp2), s);
    gtk_scrolled_window_set_max_content_width(
        (GtkScrolledWindow *)s->h->v_scroll, 500);
    gtk_window_set_title(GTK_WINDOW(s->h->v_window), (const gchar *)"uchat");
    gtk_widget_show_all((GtkWidget *)s->h->v_window);
}

void mx_send_conection(t_s *s) {
    cJSON *send = cJSON_CreateObject();
    char *res;

    cJSON_AddStringToObject(send, "kind", "connection");
    res = cJSON_Print(send);
    tls_write(s->c->tls, res, strlen(res) + 1);
}

void mx_init_chatt(t_s *s) {
    mx_1_chat_init(s);
    mx_2_chat_init(s);
    mx_3_chat_init(s);
    mx_4_chat_init(s);
    mx_5_chat_init(s);
    mx_6_chat_init(s);
    mx_7_chat_init(s);
    mx_send_conection(s);
    // gtk_window_set_position(GTK_WINDOW(s->h->v_window),
    //     GTK_WIN_POS_CENTER_ALWAYS);  !!!!
    pthread_t thread_input;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int tc = pthread_create(&thread_input, &attr, 
        (void *_Nullable(*_Nonnull)(void *_Nullable))mx_watcher_thread, s);
    
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
    if (strlen(password) > 30 || strlen(login) > 30) {
        gtk_label_set_text((GtkLabel *)s->l->e_lbl, "Password very long");
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

void mx_do_logining(GtkWidget *widget, t_s *s) {
    if (mx_check_on_input(widget, s))
        return;
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "login");
    cJSON_AddStringToObject(send, "login", s->l->login);
    cJSON_AddStringToObject(send, "pasword", s->l->pass);
    char *res = cJSON_Print(send);

    if (mx_init_server(s, s->l->argv))
        mx_exit_chat(s);
    tls_write(s->c->tls, res, strlen(res) + 1);
    mx_init_while_login(s);
}

gboolean mx_check_logining(t_s *s) {
    if (s->l->login_in) {
        s->l->login_in = 0;
        gtk_widget_hide(s->l->win);
        mx_init_chatt(s);
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
    // gtk_window_set_position(GTK_WINDOW(s->l->win), GTK_WIN_POS_CENTER_ALWAYS);!!!!
    gtk_entry_set_visibility(GTK_ENTRY(s->l->pass_ety), FALSE);
    gtk_window_set_resizable (GTK_WINDOW(s->l->win), FALSE);
    gtk_css_provider_load_from_path(s->l->SP, "src/client/theme.css", NULL);
    gtk_style_context_add_provider_for_screen( gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(s->l->SP),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_set_title(GTK_WINDOW(s->l->win), "Uchat");
    g_signal_connect(G_OBJECT(s->l->win), "destroy",
        G_CALLBACK(gtk_main_quit), s);
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
                     G_CALLBACK(mx_do_logining), s);
    gtk_container_add(GTK_CONTAINER(s->l->win), s->l->vbox);
    g_timeout_add(50, (GSourceFunc)mx_check_logining, s);
    gtk_widget_show_all(s->l->win);
    gtk_main();
}

void mx_client_init(t_s *s, int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    mx_init_logining_1(s);
    mx_init_logining_2(s);
    mx_init_logining_3(s);
    mx_init_logining_4(s);
}






int main(int argc, char **argv) {
    if (argc < 3) {
        mx_printerr("usage: uchat [ip_adress] [port]\n");
        return -1;
    }
    t_s *s = malloc(sizeof(t_s));
    // signal(SIGINT, SIG_IGN);
    s->c = malloc(sizeof(t_clt));
    s->l = malloc(sizeof(t_lgn));
    s->h = malloc(sizeof(t_ct));
    s->l->argv = argv;
    mx_client_init(s, argc, argv);
}
