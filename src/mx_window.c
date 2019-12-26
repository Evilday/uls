#include "uls.h"

int mx_num_of_cols(t_info *info) {
	struct winsize w;
	int max_len = 0;
	int cols = 0;
	int lines = 0;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next)
		if (max_len < mx_strlen(tmp->data))
			max_len = mx_strlen(tmp->data);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	cols = (w.ws_col / ((8 - (max_len % 8)) + max_len));
	lines = info->num_of_sub / cols;
		if (lines == 0 || ((info->num_of_sub % cols) != 0))
			lines++;
	info->max_sub_len = max_len;
	return lines;
}
