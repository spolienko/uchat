#include "uchat.h"

struct tls_config *mx_tls_config_new(void) {
    struct tls_config *config = NULL;

    config = tls_config_new();
    if (config == NULL) {
        printf("error tls_config_new\n");
        exit(1);
    }
    return config;
}

int mx_tls_config_parse_proto(unsigned int *p) {
    int i = tls_config_parse_protocols(p, "secure");
    if(i < 0) {
        printf("tls_config_parse_protocols error\n");
        exit(1);
    }
    return 1;
}

int mx_tls_config_set_proto(struct tls_config *conf, unsigned int p) {
    int i = tls_config_set_protocols(conf, p);
    if (i < 0) {
        printf("tls_config_set_protocols error\n");
        exit(1);
    }
    return 1;
}

int mx_tls_config_set_ca_file(struct tls_config *conf) {
    int i = tls_config_set_ca_file(conf, "./certificates/root.pem");
    if (i < 0) {
        printf("tls_config_ca_file error");
        exit(1);
    }
    return 1;
}
