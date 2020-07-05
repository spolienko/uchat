#include "libmx.h"

static char *check_zero(char *str_num) {
    str_num = mx_strnew(1);
    str_num[0] = '0';
    return str_num;
}

char *mx_itoa(int number) {
    char *str_num = NULL;
    short size = 0;
    long l = number;

    if (number < 0) {
        size++;
        l *= -1;
    }
    if (number == 0) 
        return check_zero(str_num);
    for (long a = l; a > 0; a /= 10, size++);
    str_num = mx_strnew(size);
    if (number < 0)
        str_num[0] = '-';
    for ( ; l > 0; size-- ) {
        str_num [size - 1] = l % 10  + '0';
        l /= 10;
    }
    return str_num;
}

