#include "uchat.h"

static char *create_table_users() {
    char *str = "CREATE TABLE IF NOT EXISTS users(login varchar(32) NOT NULL ";
    char *str2 = mx_strjoin(str, "PRIMARY KEY, password varchar(32) NOT NULL");
    char *str3 = mx_strjoin(str2, ", tema char(6), lang char(3))");

    mx_strdel(&str2);
    return str3;
}   /* Тут таблицы: Логин, Пароль, Тема, Язык.*/

static char *create_table_messages() {
    char *str = "CREATE TABLE IF NOT EXISTS messages(id integer primary key ";
    char *str2 = mx_strjoin(str, "NOT NULL, time varchar(32), login ");
    char *str3 = mx_strjoin(str2, "varchar(32), body text)");
    
    mx_strdel(&str2);
    return str3;
}    /* Тут таблицы: ID, Время, Логин, Текст.*/

void mx_database_init(t_data *data) {
    sqlite3 *database = data->database;
    char *errmsg;
    char *users = create_table_users();
    char *messages = create_table_messages();
    char *session = "CREATE TABLE sessions(login varchar(32) NOT NULL)";

    if (sqlite3_open("chat.sqlite", &database))
        exit(1);
    if (sqlite3_exec(database, users, 0, 0, &errmsg)){
        printf("Database error: %s\n", errmsg);
        sqlite3_close(database);
        mx_strdel(&users);
        mx_strdel(&messages);
        exit(1);
    }
    mx_strdel(&users);
    sqlite3_exec(database, messages, 0, 0, &errmsg);
    mx_strdel(&messages);
    sqlite3_exec(database, "DROP TABLE IF EXISTS sessions", 0, 0, &errmsg);
    sqlite3_exec(database, session, 0, 0, &errmsg);
}

int mx_get_msg_id(t_data *data, char *login, char *time, char *msg) {
    char *str = "SELECT id FROM messages WHERE login=? AND time=? AND body=?";
    int rc;
    int res;

    pthread_mutex_lock(&data->msg_mutex);
    sqlite3_prepare_v2(data->database, str, -1, &data->stmt, 0);
    sqlite3_bind_text(data->stmt, 1, login, strlen(login), SQLITE_STATIC);
    sqlite3_bind_text(data->stmt, 2, time, strlen(time), SQLITE_STATIC);
    sqlite3_bind_text(data->stmt, 3, msg, strlen(msg), SQLITE_STATIC);
    rc = sqlite3_step(data->stmt);
    if (rc == SQLITE_DONE) {
        sqlite3_finalize(data->stmt);
        pthread_mutex_unlock(&data->msg_mutex);
        return 0;
    }
    res = sqlite3_column_int(data->stmt, 0);
    sqlite3_finalize(data->stmt);
    pthread_mutex_unlock(&data->msg_mutex);
    return res;
}
