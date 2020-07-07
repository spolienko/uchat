#include "uchat.h"

int mx_client_worker(t_connection *conn, struct kevent *kEvent) {
    char buf[1024];
    int rc;

    rc = tls_read(conn->connection_array[kEvent->ident], buf, sizeof(buf));
    if (rc > 0 ) {
        buf[rc] = 0;
        printf("Client msg from %p: %s\n", (void *)conn->connection_array[kEvent->ident], buf);
        for(int i = 3; i <= MX_MAX_CONN; i++) {
            if ((struct tls *)conn->connection_array[i] != NULL &&
            (struct tls *)conn->connection_array[i] != (struct tls *)conn->connection_array[kEvent->ident]) {
                printf("sending messege to %d\n", i);
                tls_write((struct tls *)conn->connection_array[i], buf, strlen(buf));
            }
        }
    }
    if (rc == -1) {
        tls_close((struct tls *)conn->connection_array[kEvent->ident]);
        tls_free((struct tls *)conn->connection_array[kEvent->ident]);
    }
    return 0;
}
