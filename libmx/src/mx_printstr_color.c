#include "libmx.h"

void mx_printstr_color(const char *s, const char *color) {
    mx_printstr(color);
    mx_printstr(s);
    mx_printstr(RESET);
}

