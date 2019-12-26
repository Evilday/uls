#include "uls.h"

static void folder_print(t_info *info);
static void check_flag_h(t_info *info);

static void folder_actions(t_info *info, bool folder) {
	if (folder)
		folder_print(info);
	else
		info->first_argv = 0;
	if (info->flag_h)
		check_flag_h(info);
}

void mx_print_tabs(int n) {
	for (int i = 0; i < n; i++)
		write(1, " ", 1);
}

void mx_print_arg(t_info *info, bool folder) {
	folder_actions(info, folder);
	if (info->sub_args) {
		if (info->print_flag == '0' || info->print_flag == 'C')
			mx_basic_print(info);
		else if (info->print_flag == 'l') {
			mx_count_tabs_l(info);
			if (folder) {
				mx_printstr("total ");
				mx_printint(info->total_blocks_l);
				mx_printchar('\n');
			}
			mx_print_l(info);
		}
		else if (info->print_flag == '1')
			mx_print_1(info);
		else if (info->print_flag == 'm')
			mx_print_semicoma(info);
	}
}

static void folder_print(t_info *info) {
	if (!info->first_argv)
		mx_printchar('\n');
	if (info->num_of_arg > 1 || (info->flag_R && !info->first_argv)) {
		write(1, info->path, mx_strlen(info->path) - 1);
		mx_printstr(":");
		mx_printstr("\n");
	}
	if (info->first_argv)
		info->first_argv = 0;
}

static void check_flag_h(t_info *info) {
	char *temp_str;

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next)
		if (tmp->minor_major)
			return;
	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
		temp_str = mx_flag_h(tmp->size);
		// free(tmp->size);
		tmp->size = mx_strdup(temp_str);
		free(temp_str);
	}
}
