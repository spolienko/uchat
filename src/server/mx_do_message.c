#include "uchat.h"

void mx_drop_user(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *user = cJSON_GetObjectItemCaseSensitive(str, "login")->valuestring;

    mx_drop_user_data(data, user);
}

static int check_kind_2(char *kind) {
    if (mx_strcmp(kind, "drop_sesion") == 0)
        return 7;
    else if (mx_strcmp(kind, "connection") == 0)
        return 8;
    else if (mx_strcmp(kind, "drop_user") == 0)
        return 9;
    else if (mx_strcmp(kind, "new_password") == 0)
        return 10;
    else if (mx_strcmp(kind, "clean_chat") == 0)
        return 11;
    else if (mx_strcmp(kind, "privat_mess") == 0)
        return 12;
    return 0;
}

static int check_kind(char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *kind = cJSON_GetObjectItemCaseSensitive(str, "kind")->valuestring;

    if (mx_strcmp(kind, "login") == 0)
        return 1;
    else if (mx_strcmp(kind, "msg") == 0)
        return 2;
    else if (mx_strcmp(kind, "delete") == 0)
        return 3;
    else if (mx_strcmp(kind, "edit") == 0)
        return 4;
    else if (mx_strcmp(kind, "ui") == 0)
        return 5;
    else if (mx_strcmp(kind, "drop_acc") == 0)
        return 6;
    return check_kind_2(kind);
}


static char *do_message2(t_data *data, char *buf,
                         t_connection *conn, int res_int) {
    if (res_int == 7)
        mx_drop_user_sesion(data, buf, conn);
    else if (res_int == 8)
        return mx_initing_closing();
    else if (res_int == 9)
        return mx_drop_user_from_admin(data, buf);
    else if (res_int == 10)
        mx_change_pass(data, buf);
    else if (res_int == 11)
        return mx_delete_messages(data, buf);
    else if (res_int == 12)
        return buf;
    return NULL;
}

char *mx_do_message(t_data *data, char *buf, struct tls *tlsconn,
                    t_connection *conn) {
    int res_int = check_kind(buf); 
    
    if (res_int == 1)
        mx_do_login(data, buf, tlsconn, conn);
    else if (res_int == 2)
        return mx_do_msg(data, buf);
    else if (res_int == 3)
        return mx_do_delete(data, buf);
    else if (res_int == 4)
        return mx_do_edit(data, buf);
    else if (res_int == 5)
        mx_do_user_interface(data, buf);
    else if (res_int == 6)
        mx_drop_user(data, buf);
    return do_message2(data, buf, conn, res_int);
}
