#include "uchat.h"

void mx_do_login(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *user = cJSON_GetObjectItemCaseSensitive(str, "user")->valuestring;
    char *pas = cJSON_GetObjectItemCaseSensitive(str, "pasword")->valuestring;
    int res = 0;

    res = mx_check_login(data, user, pas);
    if (res == 1)
    /*send*/ ;//Создан новый пользователь 
    else if (res == 2)
    /*send*/ ;//Пароль и логин совпадают
    else if (res == 3)
    /*send*/ ;//Пароль не верен
    else
    /*send*/ ;//ошибка создания пользователя
    if (res == 1 || res == 2)
        mx_chat_create_session(data, user);
    mx_strdel(&user);
    cJSON_Delete(str);
}

void mx_do_msg(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *user = cJSON_GetObjectItemCaseSensitive(str, "user")->valuestring;
    char *msg = cJSON_GetObjectItemCaseSensitive(str, "msg")->valuestring;
    char *time = mx_chat_new_message(data, user, msg); //Добавили msg в БД
    int msg_id = mx_get_msg_id(data, user, time, msg);
    msg_id = 0;
    /*send*/
    mx_strdel(&time); // Заглушка
}
