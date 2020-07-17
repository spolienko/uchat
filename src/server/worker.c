#include "uchat.h"


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
    char *str = "UPDATE messages SET body=\"?1\" WHERE id=?2 AND login=\"?3\"";
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
    char *new_mess = cJSON_GetObjectItemCaseSensitive(str, "msg")->valuestring;
    char *login = cJSON_GetObjectItemCaseSensitive(str, "login")->valuestring;

    if(mx_edit(data, edit_id, new_mess, login)) {
        cJSON_AddStringToObject(send, "kind", "edit");
        cJSON_AddNumberToObject(send, "id", edit_id);
        cJSON_AddStringToObject(send, "msg", new_mess);
        return cJSON_Print(send);
    }
    return NULL;
}
// Добавить у
void change_pass_in_db(t_data *data, char *who_c, char *new_p) { //
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

void change_pass(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *who_c = cJSON_GetObjectItemCaseSensitive(str, "who_change")->valuestring;
    char *new_p = cJSON_GetObjectItemCaseSensitive(str, "new_pass")->valuestring;

    printf("%s\t%s\n", who_c, new_p);//Что приходит 
    change_pass_in_db(data, who_c, new_p);
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

char *initing_closing() {
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "connection");
    char *msg = cJSON_Print(send);
    return msg;
}

char *create_drop_call(char *drop_user) {
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "drop_user");
    cJSON_AddStringToObject(send, "drop_user", drop_user);
    char *msg = cJSON_Print(send);

    return msg;
}

char *drop_user_from_admin(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *admin = cJSON_GetObjectItemCaseSensitive(str, "admin")->valuestring;
    char *drop_user = cJSON_GetObjectItemCaseSensitive(str, "drop_user")->valuestring;
    
    if (data->argc == 4)
        if (!strcmp(admin, data->argv[3]))
            return create_drop_call(drop_user);
    return NULL;
}

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

char *delete_messages(t_data *data, char *buf) {
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

static char *do_message2(t_data *data, char *buf, t_connection *conn, int res_int) {
    if (res_int == 7)
        mx_drop_user_sesion(data, buf, conn);
    else if (res_int == 8)
        return initing_closing();
    else if (res_int == 9)
        return drop_user_from_admin(data, buf);
    else if (res_int == 10)
        change_pass(data, buf);
    else if (res_int == 11)
        return delete_messages(data, buf);
    else if (res_int == 12)
        return buf;
    else
        printf("Error reading cJSON from client\n");
    return NULL;
}

static char *do_message(t_data *data, char *buf, struct tls *tlsconn, t_connection *conn) {
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

static char *check_on_conection(char *msg, int con_id) {
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
        data->connecting = kEvent->ident;
        msg = do_message(data, buf, (struct tls *)conn->connection_array[kEvent->ident], conn);
        for(int i = 3; i <= MX_MAX_CONN; i++){
            if (msg != NULL && (struct tls *)conn->connection_array[i] != NULL ) {
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
