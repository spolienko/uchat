#include "libmx.h"

static int mx_file_len(const char *file) {
    short f = open(file, O_RDONLY);
    short sz = 0;
    int len = 0;
    char buf;

    sz = read(f, &buf, 1);
    while (sz > 0) {
        sz = read(f, &buf, 1);
	len++;
    }
    close(f);
    return len;
}

char *mx_file_to_str(const char *file) {
    int f = open(file, O_RDONLY);

    if (f == -1) {
        close(f);
        return NULL;
    }

    int sz = 0;
    int size = mx_file_len(file);
    if (size == 0)
        return NULL;
    char *newstr = mx_strnew(size);
    sz = read(f, newstr, size);
    close(f);
    return newstr;
}

