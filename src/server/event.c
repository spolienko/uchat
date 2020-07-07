#include "uchat.h"

void mx_listen_for_events(t_data *data, int kq, int sock, struct kevent *kEvent, struct timespec *t, t_connection *conn) {
    int event;
    int client;
    struct sockaddr_storage caddr;
    socklen_t clen = sizeof(caddr);

    for(;;) {
        event = kevent(kq, NULL, 0, kEvent, 1, t);
        if (event == 0)
            continue ;
        if (event == -1) {
            printf("listen to event error: %s\n", strerror(errno));
            break;
        }
        if (kEvent->ident == (uintptr_t) sock) {
            client = accept(sock, NULL, NULL);
            if(client == -1) {
                printf(" Connect from client error: %s\n", strerror(errno));
                break ;
            }
            char buff[100];
            printf("New client: %d\n", client);
            getnameinfo((struct sockaddr*)&caddr, clen,
                        buff, 100, 0, 0,
                        NI_NUMERICHOST);
            EV_SET(kEvent, client, EVFILT_READ, EV_ADD, 0, 0, 0);
            if (kevent(kq, kEvent, 1, 0, 0, NULL) == -1) {
                printf("Client kevent error: %s\n", strerror(errno));
                break;
            }

            if(tls_accept_socket(conn->tls, &conn->connection_array[client], client) < 0) {
                printf("tls_accept_socket error\n");
                exit(1);
            }

            if (tls_handshake(conn->connection_array[client]) < 0) {
                printf("tls_handshake error\n");
                // printf("%s\n", tls_error(conn->connection_array[client]));
                exit(1);
            }

            // mx_report_tls(conn->connection_array[client], "new client connected");
            printf("\n");
            printf("Client connected successfully\n");
        }
        else {
            if ((kEvent->fflags & EV_EOF) != 0) {
                printf("Client disconected");
                close(kEvent->ident);
                tls_close(conn->connection_array[kEvent->ident]);
                tls_free(conn->connection_array[kEvent->ident]);
            }
            else {
                if((mx_client_worker(conn, kEvent, data) == -1)) {
                    printf("error");
                    break ;
                }
            }
        }
    }
}
