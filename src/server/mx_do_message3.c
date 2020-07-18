#include "uchat.h"


void delete_from_bd_all_mess (t_data *data) {
    char *str2 = "DELETE FROM messages where 1=1";

    sqlite3_prepare_v2(data->database, str2, -1, &data->stmt, 0);
    if(sqlite3_step(data->stmt) != SQLITE_DONE)
        puts("Failed to delete all mess");
    sqlite3_finalize(data->stmt);
}

char *create_delete_all_mess() {
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "drop_all_mess");
    return cJSON_Print(send);
}

char *mx_delete_messages(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *who_drop = cJSON_GetObjectItemCaseSensitive(str, "who_clean")->valuestring;

    if (data->argc == 4) {
        if (!strcmp(who_drop, data->argv[3])) {
            delete_from_bd_all_mess(data);
            return create_delete_all_mess();
        }
    }
    return NULL;
}
