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

int mx_edit(t_data *data, int edit_id, char *new_mess, char *login) {
    sqlite3_stmt *stmt = data->stmt;
    char *str = "UPDATE messages SET body=\"?1\" "
        "WHERE id=?2 AND login=\"?3\"";
    int ret = 0;

    sqlite3_prepare_v2(data->database, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, new_mess,
                      strlen(new_mess), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, mx_itoa(edit_id),
                      strlen(mx_itoa(edit_id)), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, login,
                      strlen(login), SQLITE_STATIC);
    if(sqlite3_step(stmt) == SQLITE_DONE)
        ret = 1;
    sqlite3_finalize(stmt);
    return ret;
}

char *mx_do_edit(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    cJSON *send = cJSON_CreateObject();
    int edit_id = cJSON_GetObjectItemCaseSensitive(str, "edit_id")->valueint;
    char *new_mess = cJSON_GetObjectItemCaseSensitive(str,
        "msg")->valuestring;
    char *login = cJSON_GetObjectItemCaseSensitive(str, "login")->valuestring;

    if(mx_edit(data, edit_id, new_mess, login)) {
        cJSON_AddStringToObject(send, "kind", "edit");
        cJSON_AddNumberToObject(send, "id", edit_id);
        cJSON_AddStringToObject(send, "msg", new_mess);
        return cJSON_Print(send);
    }
    return NULL;
}

