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

static char *do_message(t_data *data, char *buf) {
    char *res = NULL;
    
    switch (check_kind(buf)) {
        case 1:
            mx_do_login(data, buf);
        case 2:
            res = mx_do_msg(data, buf);
        case 3: //delete
            res = NULL;/* code */
        case 4://edit
            res = NULL;/* code */
        case 5:
            mx_do_user_interface(data, buf);
        default:
            printf("Error reading cJSON from client\n");
        }
    return res;
}

int mx_client_worker(t_connection *conn, struct kevent *kEvent, t_data *data) {
    char buf[1024];
    int rc;
    char *msg;

    rc = tls_read(conn->connection_array[kEvent->ident], buf, sizeof(buf));
    if (rc > 0 ) {
        buf[rc] = 0;
        msg = do_message(data, buf);// Тут мне нужен сокет 
        for(int i = 3; i <= MX_MAX_CONN; i++)
            if ((struct tls *)conn->connection_array[i] != NULL &&
            (struct tls *)conn->connection_array[i] != (struct tls *)conn->connection_array[kEvent->ident]) {
                printf("sending messege to %d\n", i);
                tls_write((struct tls *)conn->connection_array[i], msg, strlen(msg));
            }
    }
    if (rc == -1) {
        tls_close((struct tls *)conn->connection_array[kEvent->ident]);
        tls_free((struct tls *)conn->connection_array[kEvent->ident]);
    }
    return 0;
}
