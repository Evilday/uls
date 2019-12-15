#include "uls.h"

//static void flag_R_recurtion(t_info *info, char *arg);

void mx_flag_R(t_info *info, char *arg) {
	t_uni_list *all_inside = NULL;

	mx_push_uni_list_back(&(all_inside), ".", ".", 0);
	mx_look_sub_argv(info, arg, all_inside);
	mx_pop_uni_list_front(&(all_inside));
	mx_sort_uni_list(all_inside);
	info->sub_args = all_inside;
	if (info->flags_exist)
		mx_work_with_flags(info);
	mx_print_arg(info, 1);
	if (info->top_flag == 'l')
		for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next)
			mx_pop_info_l_front(&(info->info_l));
	for (t_uni_list *tmp = all_inside; tmp; tmp = tmp->next)
		if (tmp->folder)
			mx_flag_R(info, tmp->path);
	for (t_uni_list *tmp = all_inside; tmp; tmp = tmp->next)
		mx_pop_uni_list_front(&(all_inside));
}

// static void flag_R_recurtion(t_info *info, char *arg) {
// 	mx_look_sub_argv(info, arg);
// 	mx_sort_uni_list(info->sub_args);
// 	if (info->flags_exist)
// 		mx_work_with_flags(info);
// 	mx_print_arg(info, folder);
// 	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next)
// 		mx_pop_uni_list_front(&(info->sub_args));
// 	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next)
// 		mx_pop_info_l_front(&(info->info_l));
// }
