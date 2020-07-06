#include "uchat.h"

void mx_chat_delete_last_message(t_data data, const char *login) {
    sqlite3 *db = data.database;
    sqlite3_stmt *stmt = data.stmt;
    pthread_mutex_t msg_mutex = PTHREAD_MUTEX_INITIALIZER;
    char *str = "DELETE FROM messages WHERE kind = 'r' AND ROWID=(SELECT MAX"; // Переделать, удалили тип сообщений
    char *res = mx_strjoin(str, "(ROWID) FROM messages WHERE login=?)");

    pthread_mutex_lock(&msg_mutex);
    sqlite3_prepare_v2(db, res, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, login, strlen(login), SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE)
        puts("Failed to delete message");
    else
        puts("Last message deleted");
    sqlite3_finalize(stmt);
    pthread_mutex_unlock(&msg_mutex);
    free(res);
    res = NULL;
}

void mx_chat_delete_session(t_data data, const char *login) {
    sqlite3 *db = data.database;
    sqlite3_stmt *stmt = data.stmt;
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
    free(res);
    res = NULL;
}
