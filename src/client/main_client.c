#include "client.h"


static void mx_client_init(t_s *s, int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    mx_init_logining_1(s);
    mx_init_logining_2(s);
    mx_init_logining_3(s);
    mx_init_logining_4(s);
}


int main(int argc, char **argv) {
    if (argc < 3) {
        mx_printerr("usage: uchat [ip_adress] [port]\n");
        return -1;
    }
    t_s *s = malloc(sizeof(t_s));
    
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    s->c = malloc(sizeof(t_clt));
    s->l = malloc(sizeof(t_lgn));
    s->h = malloc(sizeof(t_ct));
    s->l->argv = argv;
    mx_client_init(s, argc, argv);
}
