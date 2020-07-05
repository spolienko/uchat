#include "uchat.h"

int mx_client_worker(struct tls *tls_accept) {
    char buf[1024];
    int rc;

    rc = tls_read(tls_accept, buf, sizeof(buf));
    if (rc > 0 ) {
        buf[rc] = 0;
        printf("Client msg: %s\n", buf);
        tls_write(tls_accept, buf, strlen(buf));
    }
    if (rc == -1 ) {
        tls_close(tls_accept);
        tls_free(tls_accept);
    }
    return 0;
}
