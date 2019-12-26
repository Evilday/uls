#include "uls.h"

static void end_this_shit(t_info *info);

void mx_flag_d(t_info *info) {
	t_uni_list *tmp;

	if (!info->file_exist && !info->folder_exist)
		mx_default_args(info);
	for (int i = 0; i < info->argc; i++)
		if (info->where_what[i] == 2 || info->where_what[i] == 3) {
			mx_push_uni_list_back(info, &info->sub_args, info->argv[i], 0);
			info->num_of_sub++;
		}
	if (info->flags_exist)
		mx_work_with_flags(info);
	tmp = info->sub_args;
	for (int i = 0; i < info->argc; i++)
		if (info->where_what[i] == 2 || info->where_what[i] == 3) {
			free(tmp->data);
			tmp->data = mx_strdup(info->argv[i]);
			tmp = tmp->next;
		}
	end_this_shit(info);
}

static void end_this_shit(t_info *info) {
	mx_sort_uni_list(info, info->sub_args);
	mx_print_arg(info, 0);
	while (info->sub_args)
		mx_pop_uni_list_front(&(info->sub_args));
	mx_clear_all(info);
}
