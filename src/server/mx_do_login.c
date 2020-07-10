#include "uchat.h"

void mx_do_login(t_data *data, char *buf, struct tls *tlscon) {
    cJSON *str = cJSON_Parse(buf);
    char *user = cJSON_GetObjectItemCaseSensitive(str, "login")->valuestring;
    char *msg = cJSON_GetObjectItemCaseSensitive(str, "pasword")->valuestring;
    int res = 0;

    res = mx_check_login(data, user, msg);
    mx_strdel(&msg);
    if (res == 1 || res == 2) {
        msg =  mx_login_back(data, true, user);
        mx_chat_create_session(data, user);
    }
    else if (res == 3 || res == 0)
        msg =  mx_login_back(data, false, user);
    tls_write(tlscon, msg, strlen(msg));
    mx_strdel(&user);
}

static char *get_user_tema(t_data *data, char *login) {
    char *str = "SELECT tema FROM users WHERE login=?";
    char *tema;

    sqlite3_prepare_v2(data->database, str, -1, &data->stmt, 0);
    sqlite3_bind_text(data->stmt, 1, login, strlen(login), SQLITE_STATIC);
    if(sqlite3_step(data->stmt) != SQLITE_ROW) {
        sqlite3_finalize(data->stmt);
        return NULL;
    }
    tema = strdup((char *)sqlite3_column_text(data->stmt, 0));
    sqlite3_finalize(data->stmt);
    return tema;
}

static char *get_user_lang(t_data *data, char *login) {
    char *str = "SELECT lang FROM users WHERE login=?";
    char *lang;

    sqlite3_prepare_v2(data->database, str, -1, &data->stmt, 0);
    sqlite3_bind_text(data->stmt, 1, login, strlen(login), SQLITE_STATIC);
    if (sqlite3_step(data->stmt) != SQLITE_ROW) {
        sqlite3_finalize(data->stmt);
        return NULL;
    }
    lang = strdup((char *)sqlite3_column_text(data->stmt, 0));
    sqlite3_finalize(data->stmt);
    return lang;
}

char *mx_login_back(t_data *data, int status, char *login) {
    cJSON *send = cJSON_CreateObject();
    char *tema = get_user_tema(data, login);
    char *lang = get_user_lang(data, login);
    char *res;

    cJSON_AddStringToObject(send, "kind", "login");
    if (status) {
        cJSON_AddNumberToObject(send, "status", status);
        cJSON_AddStringToObject(send, "tema", tema);
        cJSON_AddStringToObject(send, "lang", lang);
    }
    else
        cJSON_AddNumberToObject(send, "status", status);
    res = cJSON_Print(send);
    mx_strdel(&tema);
    mx_strdel(&lang);
    return res;
}
