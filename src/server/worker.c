#include "uchat.h"

static int check_kind(char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *kind = cJSON_GetObjectItemCaseSensitive(str, "kind")->valuestring;
    int res = 0; 

    if (mx_strcmp(kind, "login") == 0)
        res = 1;
    else if (mx_strcmp(kind, "msg") == 0)
        res = 2;
    else if (mx_strcmp(kind, "delete") == 0)
        res = 3;
    else if (mx_strcmp(kind, "edit") == 0)
        res = 4;
    else if (mx_strcmp(kind, "ui") == 0)
        res = 5;
    else if (mx_strcmp(kind, "drop_acc") == 0)
        res = 6;
    return res;
}

// char *mx_do_delete()


// char * mx_drop(t_data *data, char *log, char *msg) {
//     sqlite3_stmt *stmt = data->stmt;/* Вставка сообщения в messages */
//     char *str = "INSERT INTO messages(time, login, body) VALUES (?1, ?2, ?3)";
//     char *msg_time = mx_time_to_str();

//     sqlite3_prepare_v2(data->database, str, -1, &stmt, 0);
//     sqlite3_bind_text(stmt, 1, msg_time, strlen(msg_time), SQLITE_STATIC);
//     sqlite3_bind_text(stmt, 2, log, strlen(log), SQLITE_STATIC);
//     sqlite3_bind_text(stmt, 3, msg, strlen(msg), SQLITE_STATIC);
//     if(sqlite3_step(stmt) != SQLITE_DONE)
//         printf("Error add message to database\n");
//     sqlite3_finalize(stmt);
//     return msg_time;
// }

// char *mx_do_msg(t_data *data, char *buf) {
//     cJSON *str = cJSON_Parse(buf);
//     cJSON *send = cJSON_CreateObject();
//     char *user = cJSON_GetObjectItemCaseSensitive(str, "login")->valuestring;
//     char *msg = cJSON_GetObjectItemCaseSensitive(str, "msg")->valuestring;
//     char *time = mx_chat_new_message(data, user, msg); //Добавили msg в БД
//     int msg_id = mx_get_msg_id(data, user, time, msg);
    
//     cJSON_AddStringToObject(send, "kind", "msg");
//     cJSON_AddStringToObject(send, "login", user);
//     cJSON_AddStringToObject(send, "msg", msg);
//     cJSON_AddStringToObject(send, "time", time);
//     cJSON_AddNumberToObject(send, "id", msg_id);
//     mx_strdel(&msg);
//     msg = cJSON_Print(send);
//     return msg;
// }

void mx_drop(t_data *data, int id) {
    sqlite3_stmt *stmt = data->stmt;/* Вставка сообщения в messages */
    char *str = "DELETE FROM messages WHERE id=?1";

    sqlite3_prepare_v2(data->database, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, mx_itoa(id), strlen(mx_itoa(id)), SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE)
        printf("Error add message to database\n");
    sqlite3_finalize(stmt);
}

char *mx_do_delete(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    cJSON *send = cJSON_CreateObject();
    int dropid = cJSON_GetObjectItemCaseSensitive(str, "id")->valueint;
    printf("%s\n", buf);

    mx_drop(data, dropid);
    cJSON_AddStringToObject(send, "kind", "delete");
    cJSON_AddNumberToObject(send, "id", dropid);
    char *msg = cJSON_Print(send);
    return msg;
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

static char *do_message(t_data *data, char *buf, struct tls *tlsconn) {
    char *res = NULL;
    
    switch (check_kind(buf)) {
        case 1:
            mx_do_login(data, buf, tlsconn);
            break;
        case 2:
            res = mx_do_msg(data, buf);
            break;
        case 3: //delete
            res = mx_do_delete(data, buf);
            break;
        case 4://edit
            res = NULL;/* code */
            break;
        case 5:
            mx_do_user_interface(data, buf);
            break;
        case 6:
            mx_drop_user(data, buf);
            break;         
        default:
            printf("Error reading cJSON from client\n");
        }
    return res;
}

int mx_client_worker(t_connection *conn, struct kevent *kEvent, t_data *data) {
    char buf[1024];
    int rc;
    char *msg;
    
    rc = tls_read(conn->connection_array[kEvent->ident], buf, sizeof(buf));
    if (rc > 0 ) {
        buf[rc] = 0;
        msg = do_message(data, buf, (struct tls *)conn->connection_array[kEvent->ident]);
        for(int i = 3; i <= MX_MAX_CONN; i++)
            if (msg != NULL && (struct tls *)conn->connection_array[i] != NULL ) {
                // &&            (struct tls *)conn->connection_array[i] != (struct tls *)conn->connection_array[kEvent->ident]
                printf("sending messege to %d\n", i);
                tls_write((struct tls *)conn->connection_array[i], msg, strlen(msg));
            }
    }
    if (rc == -1) {
        tls_close((struct tls *)conn->connection_array[kEvent->ident]);
        tls_free((struct tls *)conn->connection_array[kEvent->ident]);
    }
    return 0;
}
