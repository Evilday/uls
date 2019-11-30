#include "uls.h"

int mx_num_of_cols(t_info *info) {
	struct winsize w;
	int max_len = 0;
	int num_of_cols = 0;

	for (int i = 0; i < info->argc; i++)
		if (max_len < mx_strlen(info->argv[i]))
			max_len = mx_strlen(info->argv[i]);

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	printf("lines %d\n", w.ws_row);
	printf("columns %d\n", w.ws_col);
	printf("len = %d\n", max_len + 1);
	printf("num_of_cols %d\n", w.ws_col / (max_len + 1));
	return num_of_cols;
}
