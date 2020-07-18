#include "uchat.h"

static char *prepea_cjson(int id, char *time, char *login, char *msg) {
    cJSON *send = cJSON_CreateObject();
    char *res = NULL;

    cJSON_AddStringToObject(send, "kind", "msg");
    cJSON_AddNumberToObject(send, "id", id);
    cJSON_AddStringToObject(send, "time", time);
    cJSON_AddStringToObject(send, "login", login);
    cJSON_AddStringToObject(send, "msg", msg);
    cJSON_AddNumberToObject(send, "sound", 0);
    res = cJSON_Print(send);
    cJSON_Delete(send);
    return res;
}

void mx_chat_send_history(t_data *data, struct tls *tlscon) {
    int res;

    sqlite3_prepare_v2(data->database, "SELECT * FROM (SELECT *, ROWID FROM "
                      "messages ORDER BY ROWID DESC LIMIT 20) ORDER BY "
                      "ROWID ASC", -1, &data->stmt, 0);
    sqlite3_bind_int(data->stmt, 1, 10);
    res = sqlite3_step(data->stmt);
    while (res != SQLITE_DONE) {
        int id = sqlite3_column_int(data->stmt, 0);
        char *time = (char *)sqlite3_column_text(data->stmt, 1);
        char *login = (char *) sqlite3_column_text(data->stmt, 2);
        char *body = (char *) sqlite3_column_text(data->stmt, 3);
        char *msg = prepea_cjson(id, time, login, body);

        tls_write(tlscon, msg, strlen(msg));
        mx_strdel(&msg);
        res = sqlite3_step(data->stmt);
    }
    sqlite3_finalize(data->stmt);
}

static void add_lang_data(t_data *data, char *login, char *lang) {
    sqlite3_stmt *stmt = data->stmt;
    char *str2 = "UPDATE users SET lang = ?1 WHERE login = ?2";

    sqlite3_prepare_v2(data->database, str2, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, lang, 3, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, login, strlen(login), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Failed to add user lang\n");
    sqlite3_finalize(stmt);
}

void mx_chat_add_ui_data(t_data *data, char *login, char *tema, char *lang) {
    sqlite3_stmt *stmt = data->stmt;
    char *str = "UPDATE users SET tema = ?1 WHERE login = ?2";

    sqlite3_prepare_v2(data->database, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, tema, 5, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, login, strlen(login), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Failed to add user tema\n");
    sqlite3_finalize(stmt);
    add_lang_data(data, login, lang);
}
