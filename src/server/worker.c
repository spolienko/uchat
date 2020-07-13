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
    else if (mx_strcmp(kind, "drop_sesion") == 0)
        res = 7;
    else if (mx_strcmp(kind, "connection") == 0)
        res = 8;
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

// void mx_chat_create_session(t_data *data, char *login) {
//     sqlite3_stmt *stmt = data->stmt;/* Добавление онлайн пользователя в бд*/
//     char *str = "INSERT INTO sessions(login) VALUES (?)";

//     sqlite3_prepare_v2(data->database, str, -1, &stmt, 0);
//     sqlite3_bind_text(stmt, 1, login, strlen(login), SQLITE_STATIC);
//     if(sqlite3_step(stmt) != SQLITE_DONE)
//         puts("Failed to create session");
//     sqlite3_finalize(stmt); 
// }

void mx_drop_user_sesion(t_data *data, char *buf, t_connection *conn) {
    cJSON *str = cJSON_Parse(buf);
    char *user = cJSON_GetObjectItemCaseSensitive(str, "login")->valuestring;
    int drop_id = cJSON_GetObjectItemCaseSensitive(str, "drop_id")->valueint;
    sqlite3_stmt *stmt = data->stmt;
    char *str2 = "DELETE FROM sessions WHERE login=?1";
    printf("%s\n", buf);

    sqlite3_prepare_v2(data->database, str2, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, user, strlen(user), SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE)
        puts("Failed to delete from session");
    printf("Client disconected\n");
    close(drop_id);
    tls_close(conn->connection_array[drop_id]);
    tls_free(conn->connection_array[drop_id]);
    sqlite3_finalize(stmt); 
}

char *initing_closing() {
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "connection");
    char *msg = cJSON_Print(send);
    return msg;
}

static char *do_message(t_data *data, char *buf, struct tls *tlsconn, t_connection *conn) {
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
        case 7:
            mx_drop_user_sesion(data, buf, conn);
            break;
        case 8:
            res = initing_closing();
            break;        
        default:
            printf("Error reading cJSON from client\n");
        }
    return res;
}


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

// void mx_do_user_interface(t_data *data, char *buf) {
//     cJSON *str = cJSON_Parse(buf);
//     char *user = cJSON_GetObjectItemCaseSensitive(str, "login")->valuestring;
//     char *tema = cJSON_GetObjectItemCaseSensitive(str, "tema")->valuestring;
//     char *lang = cJSON_GetObjectItemCaseSensitive(str, "lang")->valuestring;

//     mx_chat_add_ui_data(data, user, tema, lang);
// }

char *check_on_conection(char *msg, int con_id) {
    cJSON *str = cJSON_Parse(msg);
    char *kind = cJSON_GetObjectItemCaseSensitive(str, "kind")->valuestring;

    if(!strcmp(kind, "connection")) {
        cJSON *send = cJSON_CreateObject();
        cJSON_AddStringToObject(send, "kind", "connection");
        cJSON_AddNumberToObject(send, "conn_id", con_id);
        msg = cJSON_Print(send);
    }
    return msg;
} 

int mx_client_worker(t_connection *conn, struct kevent *kEvent, t_data *data) {
    char buf[1024];
    int rc;
    char *msg;
    
    rc = tls_read(conn->connection_array[kEvent->ident], buf, sizeof(buf));
    if (rc > 0 ) {
        buf[rc] = 0;
        msg = do_message(data, buf, (struct tls *)conn->connection_array[kEvent->ident], conn);
        for(int i = 3; i <= MX_MAX_CONN; i++){
            if (msg != NULL && (struct tls *)conn->connection_array[i] != NULL ) {
                // &&            (struct tls *)conn->connection_array[i] != (struct tls *)conn->connection_array[kEvent->ident]
                printf("sending messege to %d\n", i);
                msg = check_on_conection(msg, i);
                tls_write((struct tls *)conn->connection_array[i], msg, strlen(msg));
            }
        }
    }
    if (rc == -1) {
        tls_close((struct tls *)conn->connection_array[kEvent->ident]);
        tls_free((struct tls *)conn->connection_array[kEvent->ident]);
    }
    return 0;
}
