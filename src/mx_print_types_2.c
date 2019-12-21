#include "uls.h"

void mx_print_semicoma(t_info *info) {
	struct winsize w;
	int words_len = 0;
	int temp = 0;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		temp = words_len;
		words_len += mx_strlen(tmp->data);
		words_len += info->p_F_flag != '0' ? 1 : 0;
		if (tmp->next)
			words_len += 2;
		if (words_len >= w.ws_col && (words_len -= temp))
			write(1, "\n", 1);
		mx_printstr(tmp->data);
		if (info->p_F_flag != '0')
			mx_flag_p_or_F(info, tmp);
		if (tmp->next)
			write(1, ", ", 2);
	}
	write(1, "\n", 1);
}
