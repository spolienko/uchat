    #include "uchat.h"

char *mx_chat_get_user_password(t_data data, char *login) {
    const char *password;
    char *res;
    char *str = "SELECT password FROM users WHERE login=?";
    int rc;

    pthread_mutex_lock(&data.msg_mutex);
    sqlite3_prepare_v2(data.database, str, -1, &data.stmt, 0);
    sqlite3_bind_text(data.stmt, 1, login, strlen(login), SQLITE_STATIC);
    rc = sqlite3_step(data.stmt);
    if(rc == SQLITE_DONE) {
        sqlite3_finalize(data.stmt);
        pthread_mutex_unlock(&data.msg_mutex);
        return 0;
    }
    password = (const char *) sqlite3_column_text(data.stmt, 0);
    res = malloc(strlen(password) + 1);
    strcpy(res, password);
    sqlite3_finalize(data.stmt);
    pthread_mutex_unlock(&data.msg_mutex);
    return res;
}

int mx_chat_create_user(t_data data, char *login, char *password, char *tema,
                        char *lang) {
    sqlite3 *db = data.database;
    sqlite3_stmt *stmt = data.stmt;
    pthread_mutex_t msg_mutex = PTHREAD_MUTEX_INITIALIZER;
    char *str = "INSERT INTO users VALUES (?, ?, ?, ?)";

    pthread_mutex_lock(&msg_mutex);
    sqlite3_prepare_v2(db, str, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, login, strlen(login), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, strlen(password), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, tema, 5, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, lang, 3, SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        pthread_mutex_unlock(&msg_mutex);
        return 0;
    }
    sqlite3_finalize(stmt);
    pthread_mutex_unlock(&msg_mutex);
    return 1;
}

void mx_chat_create_session(t_data data, char *login) {
    sqlite3 *db = data.database; /* Добавление онлайн пользователя в бд*/
    sqlite3_stmt *stmt = data.stmt;
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

static char *join_str() {
    char *str =  "INSERT INTO messages(time, login, body) ";
    char *res = mx_strjoin(str, "VALUES (?, ?, ?)");
    
    return res;
}

void mx_chat_new_message(t_data data, const char *login, const char *msg) {
    struct timeval tv; /* Вставка сообщения в messages */
    long long time_encoded;
    sqlite3 *db = data.database;
    sqlite3_stmt *stmt = data.stmt;
    pthread_mutex_t msg_mutex = PTHREAD_MUTEX_INITIALIZER;
    char *str =  join_str();

    pthread_mutex_lock(&msg_mutex);
    gettimeofday(&tv, 0);
    time_encoded = ((long long)tv.tv_sec << 32) + tv.tv_usec;
    sqlite3_prepare_v2(db, str, -1, &stmt, 0);
    sqlite3_bind_int64(stmt, 1, time_encoded);
    sqlite3_bind_text(stmt, 2, login, strlen(login), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, msg, strlen(msg), SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE)
        puts(sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    data.last_msg_id = sqlite3_last_insert_rowid(db);
    pthread_mutex_unlock(&msg_mutex);
}

