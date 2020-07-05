#include "uchat.h"

void mx_demonize(char *logfile) {
    int fd;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;
    char *dir = mx_strnew(PATH_MAX + 1);

    pid = fork();
    if (pid > 0)
        exit(0);
    umask(0);
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    getcwd(dir, PATH_MAX + 1);
    chdir(dir);
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (rlim_t i = 0; i < rl.rlim_max; i++)
        close(i);
    fd = open(logfile, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, S_IRWXU);
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
    setsid();
    free(dir);
}
