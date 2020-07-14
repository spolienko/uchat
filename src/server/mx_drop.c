#include "uchat.h"

void mx_drop(t_data *data, int id) {
    sqlite3_stmt *stmt = data->stmt;
    char *str = "DELETE FROM messages WHERE id=?1";

    sqlite3_prepare_v2(data->database, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, mx_itoa(id),
                      strlen(mx_itoa(id)), SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE)
        printf("Failed to delete message from database\n");
    sqlite3_finalize(stmt);
}

void mx_drop_user_data(t_data *data, char *login) {
    sqlite3_stmt *stmt = data->stmt;
    char *str = "DELETE FROM users WHERE login = ?1";
    
    sqlite3_prepare_v2(data->database, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, login, strlen(login), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Failed to drop\n");
    sqlite3_finalize(stmt);
}

void mx_drop_user(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *user = cJSON_GetObjectItemCaseSensitive(str, "login")->valuestring;

    mx_drop_user_data(data, user);
}

char *mx_do_delete(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    cJSON *send = cJSON_CreateObject();
    int dropid = cJSON_GetObjectItemCaseSensitive(str, "id")->valueint;

    mx_drop(data, dropid);
    cJSON_AddStringToObject(send, "kind", "delete");
    cJSON_AddNumberToObject(send, "id", dropid);
    char *msg = cJSON_Print(send);
    return msg;
}
