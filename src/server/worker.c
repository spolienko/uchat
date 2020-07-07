#include "uchat.h"


static void do_login(t_data *data, char *buf) {
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
    mx_strdel(&user);
    cJSON_Delete(str);

}

static int check_kind(char *buf) {
    cJSON *str = cJSON_Parse(buf);
    char *kind = cJSON_GetObjectItemCaseSensitive(str, "kind")->valuestring;
    int res = 0;

    if (mx_strcmp(kind, "login") == 0)
        res = 1;
    else if (mx_strcmp(kind, "msg") == 0)
        res = 2;
    else if (mx_strcmp(kind, "delete") == 0)
        res = 3;
    else if (mx_strcmp(kind, "edit") == 0)
        res = 4;
    cJSON_Delete(str);
    return res;
}

static void do_message(t_data *data, char *buf) {
    switch (check_kind(buf)) {
        case 1:
            do_login(data, buf);
            break;
        case 2: //msg
            /* code */
            break;
        case 3: //delete
            /* code */
            break;
        case 4://edit
            /* code */
            break;
        default://error
            break;
        }
}

int mx_client_worker(t_data *data, struct tls *tls_accept) {
    char buf[1024];
    int rc;

    rc = tls_read(tls_accept, buf, sizeof(buf));
    if (rc > 0 ) {
        buf[rc] = 0;
        
        do_message(data, buf);

        printf("Client msg: %s\n", buf);
        tls_write(tls_accept, buf, strlen(buf));
    }
    if (rc == -1 ) {
        tls_close(tls_accept);
        tls_free(tls_accept);
    }
    return 0;
}
