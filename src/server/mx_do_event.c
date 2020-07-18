#include "uchat.h"

static void accept_connection(int sock, struct kevent *kEvent,
    t_connection *conn, int kq, struct sockaddr_storage *caddr) {
    int client;
    char buff[100];
    socklen_t clen = sizeof(*caddr);

    client = accept(sock, NULL, NULL);
    if (client == -1)
        return ;
    getnameinfo((struct sockaddr *)caddr, clen,
                buff, 100, 0, 0, NI_NUMERICHOST);
    EV_SET(kEvent, client, EVFILT_READ, EV_ADD, 0, 0, 0);
    if (kevent(kq, kEvent, 1, 0, 0, NULL) == -1)
        return ;
    if (tls_accept_socket(conn->tls,
        &conn->connection_array[client], client) < 0)
        exit(1);
    if (tls_handshake(conn->connection_array[client]) < 0)
        exit(1);
}

static void close_connection(t_connection *conn, struct kevent *kEvent) {
    close(kEvent->ident);
    tls_close(conn->connection_array[kEvent->ident]);
    tls_free(conn->connection_array[kEvent->ident]);
}

void mx_listen_for_events(t_data *data, int kq,
    int sock, struct kevent *kEvent, struct timespec *t, t_connection *conn) {
    int event;
    struct sockaddr_storage caddr;

    for (;;)
    {
        event = kevent(kq, NULL, 0, kEvent, 1, t);
        if (event == 0)
            continue;
        if (event == -1)
            break;
        if (kEvent->ident == (uintptr_t)sock)
            accept_connection(sock, kEvent, conn, kq, &caddr);
        else
        {
            if ((kEvent->fflags & EV_EOF) != 0)
                close_connection(conn, kEvent);
            else if ((mx_client_worker(conn, kEvent, data) == -1))
                break;
        }
    }
}
