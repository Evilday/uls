#include "uls.h"

static void basic_print(t_info *info, int num_of_lines);
static void print_1(t_info *info);

void mx_print_tabs(int n) {
	for (int i = 0; i < n; i++)
		write(1, " ", 1);
}

void mx_print_arg(t_info *info, bool folder) {
	int f = 1;

	if (folder) {
		if (info->first_argv)
			info->first_argv = 0;
		else
			mx_printchar('\n');
		if (info->num_of_arg > 1) {
			char *str = mx_up_to_one(info->sub_args->path);

			mx_printstr(str);
			free(str);
			mx_printstr(":\n");
		}
		else
			info->num_of_arg = 0;
	}
	else
		info->first_argv = 0;

	if (info->all_our_flags) {
		for (int i = mx_strlen(info->all_our_flags) - 1; i >= 0; i--) {
			if (info->all_our_flags[i] == 'l' && f--) {
				mx_count_tabs_l(info);
				if (folder) {
					mx_printstr("total ");
					mx_printint(info->total_blocks_l);
					mx_printchar('\n');
				}
				mx_print_l(info);
				info->total_blocks_l = 0;
				break;
			}
			else if (info->all_our_flags[i] == '1' && f--) {
				print_1(info);
				break;
			}
		}
	}
	if (f) {
		int num_of_lines = mx_num_of_cols(info);

		basic_print(info, num_of_lines);
	}
}

static void basic_print(t_info *info, int num_of_lines) {
	int j;
	int sub_r;
	int tab_len = 0;

	for (int i = 0; i < num_of_lines; i++) {
		j = 0;
		sub_r = 0;
		for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next, j++) {
			if ((j + num_of_lines - i) % num_of_lines == 0) {
				mx_printstr(tmp->data);
				if (sub_r + num_of_lines < info->num_of_sub) {
					tab_len = info->max_sub_len - mx_strlen(tmp->data);
					mx_print_tabs(tab_len + (8 - (info->max_sub_len % 8)));
				}
			}
			++sub_r;
		}
		mx_printchar('\n');
	}
}

static void print_1(t_info *info) {
	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		mx_printstr(tmp->data);
		mx_printchar('\n');
	}
	mx_printchar('\n');
}
