#include "uchat.h"

int mx_start_network(int port, char *argv) {
    struct sockaddr_in server;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
    int option = 1;

    if(sock == -1) 
        exit(1);
    bzero(&server, sizeof(server));
    if(!strcmp(argv, "null"))
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
	else
        server.sin_addr.s_addr = inet_addr(argv);
    server.sin_port = htons(port);
	server.sin_family = AF_INET;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));
    if (bind(sock, (struct sockaddr *) &server, sizeof(server)) == -1) {
        close(sock);
		exit(1);
	}
    return sock;
}
