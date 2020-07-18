#include "client.h"

int mx_exit_chat(t_s *s) {
    tls_close(s->c->tls);
    tls_free(s->c->tls);
    tls_config_free(s->c->cnf);
    printf("Closing socket...\n");
    close(s->c->sock);
    printf("exit client\n");
    return 0;
}

void mx_report_1(time_t t, const char *ocsp_url, t_s *s, char *host) {
    fprintf(stderr, "\nTLS handshake negotiated %s/%s with host %s\n",
            tls_conn_version(s->c->tls), tls_conn_cipher(s->c->tls), host);
    fprintf(stderr, "Peer name: %s\n", host);
    if (tls_peer_cert_subject(s->c->tls))
        fprintf(stderr, "Subject: %s\n",
                tls_peer_cert_subject(s->c->tls));
    if (tls_peer_cert_issuer(s->c->tls))
        fprintf(stderr, "Issuer: %s\n",
                tls_peer_cert_issuer(s->c->tls));
    if ((t = tls_peer_cert_notbefore(s->c->tls)) != -1)
        fprintf(stderr, "Valid From: %s", ctime(&t));
    if ((t = tls_peer_cert_notafter(s->c->tls)) != -1)
        fprintf(stderr, "Valid Until: %s", ctime(&t));
    if (tls_peer_cert_hash(s->c->tls))
        fprintf(stderr, "Cert Hash: %s\n",
                tls_peer_cert_hash(s->c->tls));
    ocsp_url = tls_peer_ocsp_url(s->c->tls);
    if (ocsp_url != NULL)
        fprintf(stderr, "OCSP URL: %s\n", ocsp_url);
}

void mx_report_2(time_t t, t_s *s) {
    fprintf(stderr, "OCSP Stapling: %s\n",
            tls_peer_ocsp_result(s->c->tls) == NULL ?  "" :
            tls_peer_ocsp_result(s->c->tls));
    fprintf(stderr,
            " response_status=%d cert_status=%d crl_reason=%d\n",
            tls_peer_ocsp_response_status(s->c->tls),
            tls_peer_ocsp_cert_status(s->c->tls),
            tls_peer_ocsp_crl_reason(s->c->tls));
    t = tls_peer_ocsp_this_update(s->c->tls);
    fprintf(stderr, "  this update: %s",
            t != -1 ? ctime(&t) : "\n");
    t =  tls_peer_ocsp_next_update(s->c->tls);
    fprintf(stderr, "  next update: %s",
            t != -1 ? ctime(&t) : "\n");
    t =  tls_peer_ocsp_revocation_time(s->c->tls);
    fprintf(stderr, "  revocation: %s",
            t != -1 ? ctime(&t) : "\n");
}


void mx_first_serv_init(t_s *s) {
    s->c->enable = 1;
    if (tls_init() < 0) {
        printf("tls_init error\n");
        exit(1);
    }
    s->c->cnf = tls_config_new();
    s->c->tls = tls_client();
    tls_config_insecure_noverifycert(s->c->cnf);
    tls_config_insecure_noverifyname(s->c->cnf);
    if (tls_config_set_key_file(s->c->cnf, "./certificates/client.key") < 0) {
        printf("tls_config_set_key_file error\n");
        exit(1);
    }
    if (tls_config_set_cert_file(s->c->cnf, 
                                 "./certificates/client.pem") < 0) {
        printf("tls_config_set_cert_file error\n");
        exit(1);
    }
    tls_configure(s->c->tls, s->c->cnf);
    memset(&s->c->h, 0, sizeof(s->c->h));
}

int mx_second_serv_init(t_s *s, char **argv) {
    s->c->h.ai_socktype = SOCK_STREAM;
    if ((s->c->err = getaddrinfo(argv[1], argv[2], 
                                 &s->c->h, &s->c->p_ad)) != 0) {
        fprintf(stderr, "getaddrinfo()fail. (%s)\n", gai_strerror(s->c->err));
        return 1;
    }
    printf("Remote address is: ");
    getnameinfo(s->c->p_ad->ai_addr, s->c->p_ad->ai_addrlen,
                s->c->address_buffer, sizeof(s->c->address_buffer),
                s->c->service_buffer, sizeof(s->c->service_buffer),
                NI_NUMERICHOST);
    printf("%s %s\n", s->c->address_buffer, s->c->service_buffer);
    s->c->sock = socket(s->c->p_ad->ai_family,
                        s->c->p_ad->ai_socktype, s->c->p_ad->ai_protocol);
    if (s->c->sock == -1) {
        printf("error sock = %s\n", strerror(errno));
        return 1;
    }
    return 0;
}
