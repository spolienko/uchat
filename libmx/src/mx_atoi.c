#include "libmx.h"

int mx_atoi(const char *str) {
	int sign;
	int output;

	sign = 1;
	output = 0;
	while (mx_isspace(*str))
		str++;
	if (*str == '-'){
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (mx_isdigit(*str)){
		output = output * 10 + *str - '0';
		str++;
	}
	return (output * sign);
}

