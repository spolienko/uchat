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
    cJSON *send = cJSON_CreateObject();
    char *user = cJSON_GetObjectItemCaseSensitive(str, "user")->valuestring;
    char *msg = cJSON_GetObjectItemCaseSensitive(str, "msg")->valuestring;
    char *time = mx_chat_new_message(data, user, msg); //Добавили msg в БД
    int msg_id = mx_get_msg_id(data, user, time, msg);

    cJSON_AddStringToObject(send, "login", user);
    cJSON_AddStringToObject(send, "msg", msg);
    cJSON_AddStringToObject(send, "time", time);
    cJSON_AddNumberToObject(send, "id", msg_id);
    mx_strdel(&msg);
    msg = cJSON_Print(send); //Send to clients
    
}

void mx_do_user_interface(t_data *data, char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *user = cJSON_GetObjectItemCaseSensitive(str, "user")->valuestring;
    char *tema = cJSON_GetObjectItemCaseSensitive(str, "tema")->valuestring;
    char *lang = cJSON_GetObjectItemCaseSensitive(str, "lang")->valuestring;

    mx_chat_add_ui_data(data, user, tema, lang);
    cJSON_Delete(str);
}
