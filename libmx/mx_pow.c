#include "libmx.h"

double mx_pow(double n, unsigned int pow) {
    double res = 1.0;

    if (pow == 0)
        return res;

    while(pow--)
        res *= n;
    return res;
}

