#include "uchat.h"

int mx_tls_config_set_key_file(struct tls_config *conf) {
    int i = tls_config_set_key_file(conf, "./certificates/server.key");
    if (i < 0) {
        printf("tls_config_set_key_file error\n");
        exit(1);
    }
    return 1;
}

int mx_tls_config_set_cert_file(struct tls_config *conf) {
    int i = tls_config_set_cert_file(conf, "./certificates/server.pem");
    if (i < 0) {
        printf("tls_config_set_cert_file error");
        exit(1);
    }
    return 1;
}

void mx_init_tls_array(struct tls *arr[MX_MAX_CONN], int len) {
    for (int i = 0; i < len; i++) {
        arr[i] = NULL;
    }
    return ;
}

t_connection *mx_tls_start(t_connection *conn) {
    struct tls_config *config = mx_tls_config_new();
    struct tls *tls = NULL;
    unsigned int proto = 0;

    mx_tls_config_parse_proto(&proto);
    mx_tls_config_set_proto(config, proto);
    mx_tls_config_set_ca_file(config);
    mx_tls_config_set_key_file(config);
    mx_tls_config_set_cert_file(config);
    tls_config_verify_client(config);
    tls = tls_server();
    if (tls == NULL)
        exit(1);
    if (tls_configure(tls, config) < 0)
        exit(1);
    conn->config = config;
    conn->tls = tls;
    mx_init_tls_array(conn->connection_array, MX_MAX_CONN);
    return conn;
}
