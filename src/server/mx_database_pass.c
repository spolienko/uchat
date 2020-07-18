#include "uchat.h"

static void change_pass_in_db(t_data *data, char *who_c, char *new_p) {
    sqlite3_stmt *stmt = data->stmt;
    char *str2 = "UPDATE users SET password = ?1 WHERE login = ?2";
    data->hash = crypt(new_p, "1a");

    sqlite3_prepare_v2(data->database, str2, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, data->hash, strlen(data->hash), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, who_c, strlen(who_c), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Failed to change password\n");
    sqlite3_finalize(stmt);
}

void mx_change_pass(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *who_c = cJSON_GetObjectItemCaseSensitive(str,
        "who_change")->valuestring;
    char *new_p = cJSON_GetObjectItemCaseSensitive(str,
        "new_pass")->valuestring;

    change_pass_in_db(data, who_c, new_p);
}
