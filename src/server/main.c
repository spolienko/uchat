#include "uchat.h"

int main(int argc, char **argv) {
    int port;
    int network_socket;
    t_connection *conn;

    if (argc == 2) {
        port = atoi(argv[1]);
        // mx_demonize("uchat_server.log");
        conn = (t_connection*)malloc(sizeof(t_connection));
        network_socket = mx_start_network(port);
        mx_tls_start(conn);
        mx_start_server(network_socket, conn);
        printf("Server socket: %d\n", network_socket);
    }
    else {
        mx_printerr("usage: uchat_server [port]\n");
        exit(1);
    }
    close(network_socket);
    return 0;
}
