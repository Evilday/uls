#include "uls.h"

t_info *mx_info_start(int argc, char **argv) {
	t_info *info = (t_info *)malloc(sizeof(t_info));

	info->argc = argc;
	info->argv = argv;
	info->num_of_arg = 0;
	info->first_argv = 1;
	info->flags_exist = 0;
	info->args_exist = 0;
	info->where_what = (int *)malloc(sizeof(int) * argc);
	info->all_our_flags = NULL;
	info->sub_args = NULL;
	info->info_l = NULL;
	info->tabs_l = NULL;
	info->flag_a = 0;
	info->flag_A = 0;
	info->num_of_sub = 0;
	info->max_sub_len = 0;
	info->total_blocks_l = 0;
	for (int i = 0; i < argc; i++)
		info->where_what[i] = 0;
	return info;
}
