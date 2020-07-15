#include "uchat.h"



int main(int argc, char **argv) {
    int port;
    int network_socket;
    t_connection *conn;
    t_data data;

    for (int gg = 0; gg < 300;gg++){
        arr[gg] = 1;
    }
    if (argc == 2 || argc == 3 || argc == 4) {
        port = atoi(argv[1]);
        data.argc = argc;
        data.argv = argv;
        //mx_demonize("uchat_server.log");
        conn = (t_connection*)malloc(sizeof(t_connection));
        mx_database_init(&data); // Добавить компиляцию sqlite3 в Makefile
        if (argc == 3 || argc == 4)
            network_socket = mx_start_network(port, argv[2]);
        if (argc == 2)
            network_socket = mx_start_network(port, "null");
        mx_tls_start(conn);
        mx_start_server(&data, network_socket, conn);
        printf("Server socket: %d\n", network_socket);
    }
    else {
        mx_printerr("usage: uchat_server [port] && if not local [ip]\n");
        exit(1);
    }
    close(network_socket);
    return 0;
}
