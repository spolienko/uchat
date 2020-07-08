#include "uchat.h"

char *mx_chat_get_user_password(t_data *data, char *login) {
    const char *password;
    char *res;
    char *str = "SELECT password FROM users WHERE login=?1";

    pthread_mutex_lock(&data->msg_mutex);
    sqlite3_prepare_v2(data->database, str, -1, &data->stmt, 0);
    sqlite3_bind_text(data->stmt, 1, login, strlen(login), SQLITE_STATIC);
    if (sqlite3_step(data->stmt) != SQLITE_DONE) {
        sqlite3_finalize(data->stmt);
        pthread_mutex_unlock(&data->msg_mutex);
        return NULL;
    }
    password = (const char *) sqlite3_column_text(data->stmt, 0);
    res = malloc(strlen(password) + 1);
    strcpy(res, password);
    sqlite3_finalize(data->stmt);
    pthread_mutex_unlock(&data->msg_mutex);
    return res;
}

int mx_chat_create_user(t_data *data, char *login, char *password) {
    sqlite3 *db = data->database;
    sqlite3_stmt *stmt = data->stmt;
    pthread_mutex_t msg_mutex = PTHREAD_MUTEX_INITIALIZER;
    char *str = "INSERT INTO users VALUES (?, ?, ?, ?)";

    pthread_mutex_lock(&msg_mutex);
    sqlite3_prepare_v2(db, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, login, strlen(login), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, strlen(password), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, "black", 5, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, "eng", 3, SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        pthread_mutex_unlock(&msg_mutex);
        return 0;
    }
    sqlite3_finalize(stmt);
    pthread_mutex_unlock(&msg_mutex);
    return 1;
}

void mx_chat_create_session(t_data *data, char *login) {
    sqlite3 *db = data->database; /* Добавление онлайн пользователя в бд*/
    sqlite3_stmt *stmt = data->stmt;
    pthread_mutex_t msg_mutex = PTHREAD_MUTEX_INITIALIZER;
    char *str = "INSERT INTO sessions(login) VALUES (?)";

    pthread_mutex_lock(&msg_mutex);
    sqlite3_prepare_v2(db, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, login, strlen(login), SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE)
        puts("Failed to create session");
    sqlite3_finalize(stmt);
    pthread_mutex_unlock(&msg_mutex);  
}

static char *str_init() {
    char *str =  "INSERT INTO messages(time, login, body) ";
    char *res = mx_strjoin(str, "VALUES (?, ?, ?)");
    
    return res;
}

char * mx_chat_new_message(t_data *data, char *log, char *msg) {
    sqlite3 *db = data->database;   /* Вставка сообщения в messages */
    sqlite3_stmt *stmt = data->stmt;
    pthread_mutex_t msg_mutex = PTHREAD_MUTEX_INITIALIZER;
    char *str = str_init();
    char *msg_time = mx_time_to_str();

    pthread_mutex_lock(&msg_mutex);
    sqlite3_prepare_v2(db, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, msg_time, strlen(msg_time), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, log, strlen(log), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, msg, strlen(msg), SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE)
        puts(sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    pthread_mutex_unlock(&msg_mutex);
    return msg_time;
}

