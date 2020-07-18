#include "uchat.h"

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

int mx_client_worker(t_connection *conn, struct kevent *kEvent,
    t_data *data) {
    char buf[1024];
    int rc;
    char *msg;
    
    rc = tls_read(conn->connection_array[kEvent->ident], buf, sizeof(buf));
    if (rc > 0 ) {
        buf[rc] = 0;
        data->connecting = kEvent->ident;
        msg = mx_do_message(data, buf,
            (struct tls *)conn->connection_array[kEvent->ident], conn);
        for(int i = 3; i <= MX_MAX_CONN; i++){
            if (msg != NULL && (struct tls *)conn->connection_array[i]
                != NULL ) {
                msg = check_on_conection(msg, i);
                tls_write((struct tls *)conn->connection_array[i], msg,
                    strlen(msg));
            }
        }
    }
    if (rc == -1) {
        tls_close((struct tls *)conn->connection_array[kEvent->ident]);
        tls_free((struct tls *)conn->connection_array[kEvent->ident]);
    }
    return 0;
}
