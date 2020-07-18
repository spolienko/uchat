#include "uchat.h"

char *mx_chat_get_user_password(t_data *data, char *login) {
    char *password;
    char *str = "SELECT password FROM users WHERE login=?1";

    sqlite3_prepare_v2(data->database, str, -1, &data->stmt, 0);
    sqlite3_bind_text(data->stmt, 1, login, strlen(login), SQLITE_STATIC);
    if (sqlite3_step(data->stmt) != SQLITE_ROW) {
        sqlite3_finalize(data->stmt);
        return NULL;
    }
    password = strdup((const char *) sqlite3_column_text(data->stmt, 0));
    sqlite3_finalize(data->stmt);
    return password;
}

int mx_chat_create_user(t_data *data, char *login, char *password) {
    sqlite3_stmt *stmt = data->stmt;
    char *str = "INSERT INTO users(login, password,"
                " tema, lang) VALUES (?1, ?2, ?3, ?4)";

    sqlite3_prepare_v2(data->database, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, login, strlen(login), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, strlen(password), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, "black", strlen("black"), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, "eng", strlen("eng"), SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return 0;
    }
    printf("Add new user:\"%s\" to database\n", login);
    sqlite3_finalize(stmt);
    return 1;
}

void mx_chat_create_session(t_data *data, char *login) {
    sqlite3_stmt *stmt = data->stmt;/* Добавление онлайн пользователя в бд*/
    char *str = "INSERT INTO sessions(login) VALUES (?)";

    sqlite3_prepare_v2(data->database, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, login, strlen(login), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        puts("Failed to create session");
    sqlite3_finalize(stmt); 
}

char * mx_chat_new_message(t_data *data, char *log, char *msg) {
    sqlite3_stmt *stmt = data->stmt;/* Вставка сообщения в messages */
    char *str = "INSERT INTO messages(time, login, body) VALUES (?1, ?2, ?3)";
    char *msg_time = mx_time_to_str();

    sqlite3_prepare_v2(data->database, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, msg_time, strlen(msg_time), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, log, strlen(log), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, msg, strlen(msg), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Error add message to database\n");
    sqlite3_finalize(stmt);
    return msg_time;
}

