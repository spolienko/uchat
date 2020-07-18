#include "uchat.h"

char *mx_initing_closing() {
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "connection");
    char *msg = cJSON_Print(send);
    return msg;
}

static char *create_drop_call(char *drop_user) {
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "drop_user");
    cJSON_AddStringToObject(send, "drop_user", drop_user);
    char *msg = cJSON_Print(send);

    return msg;
}

char *mx_drop_user_from_admin(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *admin = cJSON_GetObjectItemCaseSensitive(str, "admin")->valuestring;
    char *drop_user = cJSON_GetObjectItemCaseSensitive(str, "drop_user")->valuestring;
    
    if (data->argc == 4)
        if (!strcmp(admin, data->argv[3]))
            return create_drop_call(drop_user);
    return NULL;
}

void mx_drop_user_sesion(t_data *data, char *buf, t_connection *conn) {
    cJSON *str = cJSON_Parse(buf);
    char *user = cJSON_GetObjectItemCaseSensitive(str, "login")->valuestring;
    int drop_id = cJSON_GetObjectItemCaseSensitive(str, "drop_id")->valueint;
    char *str2 = "DELETE FROM sessions WHERE login=?1";

    sqlite3_prepare_v2(data->database, str2, -1, &data->stmt, 0);
    sqlite3_bind_text(data->stmt, 1, user, strlen(user), SQLITE_STATIC);
    if(sqlite3_step(data->stmt) != SQLITE_DONE)
        puts("Failed to delete from session");
    printf("Client disconected\n");
    close(drop_id);
    sqlite3_finalize(data->stmt);
    (void)conn;
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
