#include "uchat.h"


// static void set_ip_address(struct sockaddr_in *serv_addr) {
//     char hostbuffer[256];
//     char *ip;
//     struct hostent *host_entry;
//     int hostname;
//     if ((hostname = gethostname(hostbuffer, sizeof(hostbuffer))) != -1) {
//         if ((host_entry = gethostbyname(hostbuffer)) != NULL) {
//             ip = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));
//             inet_aton(ip, &((*serv_addr).sin_addr));
//             mx_strdel(&ip);
//             printf("ip: %s\n", ip);
//             return;
//         }
//     }
//     inet_aton("127.0.0.1", &((*serv_addr).sin_addr));
//     printf("ip: 127.0.0.1\n");
// }
// для получения ай пи компа без ввода ай пи если это кто-то читает подойдите к вкметук


int mx_start_network(int port, char *argv) {
    struct sockaddr_in server;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
    int option = 1;

    if(sock == -1) {
        mx_printerr("Socket creation error");
        exit(1);
    }
    bzero(&server, sizeof(server));
    if(!strcmp(argv, "null"))
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
	else
        server.sin_addr.s_addr = inet_addr(argv);
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
