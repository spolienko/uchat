#include "uchat.h"

int mx_start_network(int port) {
    struct sockaddr_in server;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
    int option = 1;

    if(sock == -1) {
        mx_printerr("Socket creation error");
        exit(1);
    }
    bzero(&server, sizeof(server));
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));
    if (bind(sock, (struct sockaddr *) &server, sizeof(server)) == -1) {
		mx_printerr("erro bind please try another port\n");
        close(sock);
		exit(1);
	}
    return sock;
}
