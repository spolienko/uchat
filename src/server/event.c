#include "uchat.h"

void mx_listen_for_events(t_data *data, int kq,
int sock, struct kevent *kEvent, struct timespec *t, t_connection *conn) {
    int event;
    int client;
    struct sockaddr_storage caddr;
    socklen_t clen = sizeof(caddr);

    for(int i= 0;;i++) {
        char buff[100];

        event = kevent(kq, NULL, 0, kEvent, 1, t);
        if (event == 0)
            continue ;
        if (event == -1)
            break;
        if (kEvent->ident == (uintptr_t) sock) {
            client = accept(sock, NULL, NULL);
            if(client == -1)
                break ;
            getnameinfo((struct sockaddr*)&caddr, clen, 
                        buff, 100, 0, 0, NI_NUMERICHOST);
            EV_SET(kEvent, client, EVFILT_READ, EV_ADD, 0, 0, 0);
            if (kevent(kq, kEvent, 1, 0, 0, NULL) == -1) 
                break;
            if (tls_accept_socket(conn->tls, &conn->connection_array[client], client) < 0)
                exit(1);
            if (tls_handshake(conn->connection_array[client]) < 0) 
                exit(1);
        }
        else {
            if ((kEvent->fflags & EV_EOF) != 0) {
                close(kEvent->ident);
                tls_close(conn->connection_array[kEvent->ident]);
                tls_free(conn->connection_array[kEvent->ident]);
            }
            else
                if ((mx_client_worker(conn, kEvent, data) == -1))
                    break ;
        }
    }
}
