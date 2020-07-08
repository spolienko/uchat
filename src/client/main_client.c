#include "uchat.h"

int main(int argc, const char **argv) {
    if (argc < 3) {
        mx_printerr("usage: uchat [ip_adress] [port]\n");
        return -1;
    }

    struct addrinfo hints;
    struct addrinfo *peer_address;
    int sock;
    int err;
    int enable = 1;
    struct tls *tls = NULL;
    struct tls_config *config = NULL;

    if (tls_init() < 0) {
        printf("tls_init error\n");
        exit(1);
    }
    config = tls_config_new();
    tls = tls_client();
    tls_config_insecure_noverifycert(config);
    tls_config_insecure_noverifyname(config);

    if (tls_config_set_key_file(config, "./certificates/client.key") < 0) {
        printf("tls_config_set_key_file error\n");
        exit(1);
    }

    if (tls_config_set_cert_file(config, "./certificates/client.pem") < 0) {
        printf("tls_config_set_cert_file error\n");
        exit(1);
    }

    tls_configure(tls, config);

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    if ((err = getaddrinfo(argv[1], argv[2], &hints, &peer_address)) != 0) {
        fprintf(stderr, "getaddrinfo() failed. (%s)\n", gai_strerror(err));
        return 1;
    }
    printf("Remote address is: ");
    char address_buffer[100];
    char service_buffer[100];
    getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen,
                address_buffer, sizeof(address_buffer),
                service_buffer, sizeof(service_buffer),
                NI_NUMERICHOST);
    printf("%s %s\n", address_buffer, service_buffer);

    sock = socket(peer_address->ai_family,
                  peer_address->ai_socktype, peer_address->ai_protocol);
    if (sock == -1) {
        printf("error sock = %s\n", strerror(errno));
        return -1;
    }
    setsockopt(sock, IPPROTO_TCP, SO_KEEPALIVE, &enable, sizeof(int));
    if (connect(sock, peer_address->ai_addr, peer_address->ai_addrlen)) {
        printf("connect error = %s\n", strerror(errno));
        return -1;
    }
    freeaddrinfo(peer_address);
    printf("connect TCP sock =%d\n", sock);

    if (tls_connect_socket(tls, sock, "uchat_server") < 0) {
        printf("tls_connect error\n");
        printf("%s\n", tls_error(tls));
        exit(1);
    }
    printf("tls connect +\n");
    if (tls_handshake(tls) < 0) {
        printf("tls_handshake error\n");
        printf("%s\n", tls_error(tls));
        exit(1);
    }
    mx_report_tls_client(tls, "client");
    printf("\n");
    tls_write(tls, "TLS connect", strlen("TLS connect"));
//    printf("tls version %s\n", tls_conn_version(tls));
    char bufs[1000], bufc[1000];
    struct pollfd pfd[2];
    ssize_t rc = 0;

    pfd[0].fd = 0;
    pfd[0].events = POLLIN;
    pfd[1].fd = sock;
    pfd[1].events = POLLIN;

    while (bufc[0] != ':' && bufc[1] != 'q') {
        bzero(bufs, 1000);
        bzero(bufc, 1000);

        poll(pfd, 2, -1);
        if (pfd[0].revents & POLLIN) {
            int q = read(0, bufc, 1000);
            tls_write(tls, bufc, q);
        }

        if (pfd[1].revents & POLLIN) {
            if ((rc = tls_read(tls, bufs, 1000)) <= 0) break;
            printf("Message (%lu): %s\n", rc, bufs);
        }

    }
    tls_close(tls);
    tls_free(tls);
    tls_config_free(config);
    printf("Closing socket...\n");
    close(sock);
    printf("exit client\n");
    return 0;

}

void mx_report_tls_client(struct tls * tls_ctx, char * host) {
    time_t t;
    const char *ocsp_url;

    fprintf(stderr, "\nTLS handshake negotiated %s/%s with host %s\n",
            tls_conn_version(tls_ctx), tls_conn_cipher(tls_ctx), host);
    fprintf(stderr, "Peer name: %s\n", host);
    if (tls_peer_cert_subject(tls_ctx))
        fprintf(stderr, "Subject: %s\n",
                tls_peer_cert_subject(tls_ctx));
    if (tls_peer_cert_issuer(tls_ctx))
        fprintf(stderr, "Issuer: %s\n",
                tls_peer_cert_issuer(tls_ctx));
    if ((t = tls_peer_cert_notbefore(tls_ctx)) != -1)
        fprintf(stderr, "Valid From: %s", ctime(&t));
    if ((t = tls_peer_cert_notafter(tls_ctx)) != -1)
        fprintf(stderr, "Valid Until: %s", ctime(&t));
    if (tls_peer_cert_hash(tls_ctx))
        fprintf(stderr, "Cert Hash: %s\n",
                tls_peer_cert_hash(tls_ctx));
    ocsp_url = tls_peer_ocsp_url(tls_ctx);
    if (ocsp_url != NULL)
        fprintf(stderr, "OCSP URL: %s\n", ocsp_url);
    switch (tls_peer_ocsp_response_status(tls_ctx)) {
        case TLS_OCSP_RESPONSE_SUCCESSFUL:
            fprintf(stderr, "OCSP Stapling: %s\n",
                    tls_peer_ocsp_result(tls_ctx) == NULL ?  "" :
                    tls_peer_ocsp_result(tls_ctx));
            fprintf(stderr,
                    "  response_status=%d cert_status=%d crl_reason=%d\n",
                    tls_peer_ocsp_response_status(tls_ctx),
                    tls_peer_ocsp_cert_status(tls_ctx),
                    tls_peer_ocsp_crl_reason(tls_ctx));
            t = tls_peer_ocsp_this_update(tls_ctx);
            fprintf(stderr, "  this update: %s",
                    t != -1 ? ctime(&t) : "\n");
            t =  tls_peer_ocsp_next_update(tls_ctx);
            fprintf(stderr, "  next update: %s",
                    t != -1 ? ctime(&t) : "\n");
            t =  tls_peer_ocsp_revocation_time(tls_ctx);
            fprintf(stderr, "  revocation: %s",
                    t != -1 ? ctime(&t) : "\n");
            break;
        case -1:
            break;
        default:
            fprintf(stderr, "OCSP Stapling:  failure - response_status %d (%s)\n",
                    tls_peer_ocsp_response_status(tls_ctx),
                    tls_peer_ocsp_result(tls_ctx) == NULL ?  "" :
                    tls_peer_ocsp_result(tls_ctx));
            break;

    }
}
