#include "uchat.h"

void mx_start_server(t_data *data, int socket, t_connection *conn) {
    int kq;
    struct kevent event;
    struct timespec timeout;

    if ((kq = kqueue()) == -1) {
        close(socket);
        exit(1);
    }
    if (listen(socket, 10) == -1) {
        close(socket);
        exit(1);
    }
    EV_SET(&event, socket, EVFILT_READ, EV_ADD, 0, 0, 0);
    if (kevent(kq, &event, 1, 0, 0, NULL) == -1) {
        close(socket);
        exit(1);
    }
    timeout.tv_sec = 1;
    timeout.tv_nsec = 0;
    mx_listen_for_events(data, kq, socket, &event, &timeout, conn);
}
