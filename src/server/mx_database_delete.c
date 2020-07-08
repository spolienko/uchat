#include "uchat.h"

void mx_chat_delete_session(t_data *data, const char *login) {
    sqlite3 *db = data->database;
    sqlite3_stmt *stmt = data->stmt;
    pthread_mutex_t msg_mutex = PTHREAD_MUTEX_INITIALIZER;
    char *str = "DELETE FROM sessions WHERE ROWID=(SELECT MIN(ROWID) FROM";
    char *res = mx_strjoin(str, " sessions WHERE login=?)");

    pthread_mutex_lock(&msg_mutex);
    sqlite3_prepare_v2(db, res, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, login, strlen(login), SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE)
        puts("Failed to delete session");
    sqlite3_finalize(stmt);
    pthread_mutex_unlock(&msg_mutex);
    mx_strdel(&res);
}

int mx_check_login(t_data *data, char *login, char *pas) {
    sqlite3 *database = data->database;
    pthread_mutex_t msg_mutex = PTHREAD_MUTEX_INITIALIZER;
    char *str = "SELECT login FROM users WHERE login=?";

    pthread_mutex_lock(&msg_mutex);
    sqlite3_prepare_v2(database, str, -1, &data->stmt, 0);
    sqlite3_bind_text(data->stmt, 1, login, strlen(login), SQLITE_STATIC);
    if(sqlite3_step(data->stmt) != SQLITE_DONE) {
        sqlite3_finalize(data->stmt);
        pthread_mutex_unlock(&msg_mutex);
        return mx_chat_create_user(data, login, pas);
    }
    else {
        sqlite3_finalize(data->stmt);
        pthread_mutex_unlock(&msg_mutex);
        if (mx_strcmp(pas, mx_chat_get_user_password(data, login)) == 0)
            return 2;
    } 
    return 3;
}

char *mx_time_to_str(void) {
    struct timeval tv;
    struct tm *nowtm;
    char buf[64] = {0};
    
    gettimeofday(&tv, NULL);
    if(tv.tv_sec) {
        nowtm = localtime(&tv.tv_sec);
        strftime(buf, 64, "%d.%m.%Y %H:%M:%S", nowtm);
        return strdup(buf);
    }
    return strdup("Time reading error");
}

static void add_lang_data(t_data *data, char *login, char *lang) {
    sqlite3 *db = data->database;
    sqlite3_stmt *stmt = data->stmt;
    pthread_mutex_t msg_mutex = PTHREAD_MUTEX_INITIALIZER;
    char *str2 = "UPDATE users SET lang = ?1 WHERE login = ?2";

    pthread_mutex_lock(&msg_mutex);
    sqlite3_prepare_v2(db, str2, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, lang, 3, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, login, strlen(login), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Failed to add user lang\n");
    sqlite3_finalize(stmt);
    pthread_mutex_unlock(&msg_mutex);
}

void mx_chat_add_ui_data(t_data *data, char *login, char *tema, char *lang) {
    sqlite3 *db = data->database;
    sqlite3_stmt *stmt = data->stmt;
    pthread_mutex_t msg_mutex = PTHREAD_MUTEX_INITIALIZER;
    char *str = "UPDATE users SET tema = ?1 WHERE login = ?2";

    pthread_mutex_lock(&msg_mutex);
    sqlite3_prepare_v2(db, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, tema, 5, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, login, strlen(login), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Failed to add user tema\n");
    sqlite3_finalize(stmt);
    pthread_mutex_unlock(&msg_mutex);
    add_lang_data(data, login, lang);
}
