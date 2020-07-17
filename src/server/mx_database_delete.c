#include "uchat.h"

void mx_chat_delete_session(t_data *data, const char *login) {
    sqlite3_stmt *stmt = data->stmt;
    char *str = "DELETE FROM sessions WHERE ROWID=(SELECT MIN(ROWID) FROM"
                " sessions WHERE login=?)";

    sqlite3_prepare_v2(data->database, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, login, strlen(login), SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE)
        puts("Failed to delete session");
    sqlite3_finalize(stmt);
}

int result(void *exist, int argc, char **argv, char **reg) {
    (void)argv;
    (void)argc;
    (void)reg;
    *(int *)exist = 1;
    return 0;
}

int mx_check_in_session(t_data *data, char *login) {
    char cmd[1024];
    int exist = 0;
    
    sprintf(cmd, "SELECT * FROM sessions WHERE login=\"%s\"", login);
    sqlite3_exec(data->database, cmd, result, &exist, NULL);
    return exist;
}

int mx_check_login(t_data *data, char *login, char *pas) {
    char *str = "SELECT login FROM users WHERE login=?";

    if (mx_check_in_session(data, login))
        return 0;
    sqlite3_prepare_v2(data->database, str, -1, &data->stmt, 0);
    sqlite3_bind_text(data->stmt, 1, login, strlen(login), SQLITE_STATIC);
    if(sqlite3_step(data->stmt) != SQLITE_ROW) {
        sqlite3_finalize(data->stmt);
        return mx_chat_create_user(data, login, pas);
    }
    else {
        sqlite3_finalize(data->stmt);
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
    sqlite3_stmt *stmt = data->stmt;
    char *str2 = "UPDATE users SET lang = ?1 WHERE login = ?2";

    sqlite3_prepare_v2(data->database, str2, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, lang, 3, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, login, strlen(login), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Failed to add user lang\n");
    sqlite3_finalize(stmt);
}

void mx_chat_add_ui_data(t_data *data, char *login, char *tema, char *lang) {
    sqlite3_stmt *stmt = data->stmt;
    char *str = "UPDATE users SET tema = ?1 WHERE login = ?2";

    sqlite3_prepare_v2(data->database, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, tema, 5, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, login, strlen(login), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Failed to add user tema\n");
    sqlite3_finalize(stmt);
    add_lang_data(data, login, lang);
}
