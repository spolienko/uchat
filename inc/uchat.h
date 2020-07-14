#ifndef UCHAT_H
#define UCHAT_H

#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <time.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <time.h>

#include "../libressl/include/tls.h"
#include "../libressl/include/openssl/evp.h"
#include "../libressl/include/openssl/sha.h"
#include "../libressl/include/openssl/aes.h"
#include "../libressl/include/openssl/conf.h"

#include <sqlite3.h>
#include "cJSON.h"
#include "../libmx/inc/libmx.h"

#define MX_MAX_CONN 100


typedef struct s_data {
    sqlite3 *database;
    pthread_mutex_t msg_mutex;
    sqlite3_stmt *stmt;
    long long last_msg_id;
    int connecting;
    char *hash;
    char **argv;
    int argc;
} t_data;

typedef struct s_connection {
    struct tls_config *config;
    struct tls *connection_array[MX_MAX_CONN];
    struct tls *tls;
} t_connection;

void mx_database_init(t_data *data);
char *mx_chat_get_user_password(t_data *data, char *login);
int mx_chat_create_user(t_data *data, char *login, char *password);
void mx_chat_create_session(t_data *data, char *login);
char * mx_chat_new_message(t_data *data, char *login, char *msg);
int mx_check_login(t_data *data, char *login, char *pas);
void mx_do_login(t_data *data, char *buf, struct tls *tlscon, t_connection *conn);
char *mx_time_to_str(void);
char *mx_do_msg(t_data *data, char *buf);
int mx_get_msg_id(t_data *data, char *login, char *time, char *msg);
void mx_chat_add_ui_data(t_data *data, char *login, char *tema, char *lang);
void mx_do_user_interface(t_data *data, char *buf);
char *mx_login_back(t_data *data, int status, char *login);
void mx_chat_send_history(t_data *data, struct tls *tlscon);
void mx_drop_user_sesion(t_data *data, char *buf);
void mx_drop_user_data(t_data *data, char *login);
void mx_drop_user(t_data *data, char *buf);
void mx_drop(t_data *data, int id);
char *mx_do_delete(t_data *data, char *buf);

/* server */

void mx_start_server(t_data *data, int socket, t_connection *conn);
void mx_demonize(char *logfile);
int mx_client_worker(t_connection *conn, struct kevent *kEvent, t_data *data);
void mx_listen_for_events(t_data *data, int kq, int sock, struct kevent *kEvent, struct timespec *t, t_connection *conn);
struct tls_config *mx_tls_config_new(void);
int mx_tls_config_parse_proto(unsigned int *p);
int mx_tls_config_set_proto(struct tls_config *conf, unsigned int p);
int mx_tls_config_set_ca_file(struct tls_config *conf);
int mx_tls_config_set_key_file(struct tls_config *conf);
int mx_tls_config_set_cert_file(struct tls_config *conf);
void mx_init_tls_array(struct tls *arr[MX_MAX_CONN], int len);
t_connection *mx_tls_start(t_connection *conn);
int mx_start_network(int port, char *argv);

/* client */

// void mx_report_tls_client(struct tls * tls_ctx, char * host);

int arr[300];


#endif

