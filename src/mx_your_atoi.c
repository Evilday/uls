#include "uls.h"

long long int my_atoi(const char *str) {
	long long int output = 0;

	while (*str > 47 && *str < 58){
		output = output * 10 + *str - '0';
		str++;
	}
	return output;
}
