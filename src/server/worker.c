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
    else if (mx_strcmp(kind, "drop_acc") == 0)
        res = 6;
    else if (mx_strcmp(kind, "drop_sesion") == 0)
        res = 7;
    else if (mx_strcmp(kind, "connection") == 0)
        res = 8;
    return res;
}

static char *initing_closing() {
    cJSON *send = cJSON_CreateObject();

    cJSON_AddStringToObject(send, "kind", "connection");
    char *msg = cJSON_Print(send);
    return msg;
}

static char *do_message(t_data *data, char *buf, struct tls *tlsconn, t_connection *conn) {
    char *res = NULL;
    
    switch (check_kind(buf)) {
        case 1:
            mx_do_login(data, buf, tlsconn, conn);
            break;
        case 2:
            res = mx_do_msg(data, buf);
            break;
        case 3:
            res = mx_do_delete(data, buf);
            break;
        case 4:
            res = NULL;
            break;
        case 5:
            mx_do_user_interface(data, buf);
            break;
        case 6:
            mx_drop_user(data, buf);
            break;   
        case 7:
            mx_drop_user_sesion(data, buf);
            break;
        case 8:
            res = initing_closing();
            break;      
        default:
            printf("Error reading cJSON from client\n");
        }
    return res;
}

static char *check_on_conection(char *msg, int con_id) {
    cJSON *str = cJSON_Parse(msg);
    char *kind = cJSON_GetObjectItemCaseSensitive(str, "kind")->valuestring;

    if(!strcmp(kind, "connection")) {
        cJSON *send = cJSON_CreateObject();

        cJSON_AddStringToObject(send, "kind", "connection");
        cJSON_AddNumberToObject(send, "conn_id", con_id);
        msg = cJSON_Print(send);
    }
    return msg;
} 

int mx_client_worker(t_connection *conn, struct kevent *kEvent, t_data *data) {
    char buf[1024];
    int rc;
    char *msg;
    
    rc = tls_read(conn->connection_array[kEvent->ident], buf, sizeof(buf));
    if (rc > 0 ) {
        buf[rc] = 0;
        data->connecting = kEvent->ident;
        msg = do_message(data, buf, (struct tls *)
                         conn->connection_array[kEvent->ident], conn);
        for(int i = 3; i <= MX_MAX_CONN; i++)
            if (msg != NULL
                && (struct tls *)conn->connection_array[i] != NULL ) {
                msg = check_on_conection(msg, i);
                tls_write((struct tls *)conn->connection_array[i], msg,
                          strlen(msg));
            }
    }
    if (rc == -1) {
        tls_close((struct tls *)conn->connection_array[kEvent->ident]);
        tls_free((struct tls *)conn->connection_array[kEvent->ident]);
    }
    return 0;
}
