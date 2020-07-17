#include "client.h"

void mx_report_tls_client(t_s *s, char *host) {
    time_t t = 0;
    const char *ocsp_url;

    mx_report_1(t, ocsp_url, s, host);
    switch (tls_peer_ocsp_response_status(s->c->tls)) {
        case TLS_OCSP_RESPONSE_SUCCESSFUL:
            mx_report_2(t, s);
            break;
        case -1:
            break;
        default:
            fprintf(stderr, "OCSP Stapling: fail-response_status %d (%s)\n",
                    tls_peer_ocsp_response_status(s->c->tls),
                    tls_peer_ocsp_result(s->c->tls) == NULL ?  "" :
                    tls_peer_ocsp_result(s->c->tls));
            break;
    }
}






int mx_third_serv_init(t_s *s) {
    setsockopt(s->c->sock, IPPROTO_TCP, SO_KEEPALIVE,
               &s->c->enable, sizeof(int));
    if (connect(s->c->sock, s->c->p_ad->ai_addr, s->c->p_ad->ai_addrlen)) {
        printf("connect error = %s\n", strerror(errno));
        return 1;
    }
    freeaddrinfo(s->c->p_ad);
    printf("connect TCP sock =%d\n", s->c->sock);
    if (tls_connect_socket(s->c->tls, s->c->sock, "uchat_server") < 0) {
        printf("tls_connect error\n");
        printf("%s\n", tls_error(s->c->tls));
        exit(1);
    }
    printf("tls connect +\n");
    return 0;
}

int mx_init_server(t_s *s, char **argv) {
    mx_first_serv_init(s);
    if (mx_second_serv_init(s, argv))
        return 1;
    if (mx_third_serv_init(s))
        return 1;
    if (tls_handshake(s->c->tls) < 0) {
        printf("tls_handshake error\n");
        printf("%s\n", tls_error(s->c->tls));
        exit(1);
    }
    mx_report_tls_client(s, "client");
    printf("\n");
    s->c->rc = 0;
    s->c->pfd[0].fd = 0;
    s->c->pfd[0].events = POLLIN;
    s->c->pfd[1].fd = s->c->sock;
    s->c->pfd[1].events = POLLIN;
    return 0;
}
