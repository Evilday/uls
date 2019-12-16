#include "uls.h"

static void folder_print(t_info *info);

void mx_print_tabs(int n) {
	for (int i = 0; i < n; i++)
		write(1, " ", 1);
}

void mx_print_arg(t_info *info, bool folder) {
	if (folder)
		folder_print(info);
	else
		info->first_argv = 0;
	if (info->top_flag == '0' || info->top_flag == 'S')
		mx_basic_print(info);
	else if (info->top_flag == 'l') {
		mx_count_tabs_l(info);
		if (folder) {
			mx_printstr("total ");
			mx_printint(info->total_blocks_l);
			mx_printchar('\n');
		}
		mx_print_l(info);
	}
	else if (info->top_flag == '1') {
		mx_print_1(info);
	}
}

static void folder_print(t_info *info) {
	if (info->first_argv)
		info->first_argv = 0;
	else {
		mx_printchar('\n');
		if (info->num_of_arg > 1 || info->flag_R) {
			mx_printstr(info->path);
			mx_printstr(":");
			if (info->num_of_sub)
				mx_printstr("\n");
		}
	}
}
