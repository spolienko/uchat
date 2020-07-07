#include "uchat.h"

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
    else if (mx_strcmp(kind, "ui") == 0)
        res = 5;
    cJSON_Delete(str);
    return res;
}



static void do_message(t_data *data, char *buf) {
    switch (check_kind(buf)) {
        case 1:
            mx_do_login(data, buf);
            break;
        case 2:
            mx_do_msg(data, buf);
            break;
        case 3: //delete
            /* code */
            break;
        case 4://edit
            /* code */
            break;
        case 5:
            mx_do_user_interface(data, buf);
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
