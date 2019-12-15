#include "uls.h"

static void default_args(t_info *info);

void mx_work_with_one_arg(t_info *info, char *arg, bool folder) {
	mx_look_sub_argv(info, arg);
	mx_sort_uni_list(info->sub_args);
	if (info->flags_exist)
		mx_work_with_flags(info);
	mx_print_arg(info, folder);
	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next)
		mx_pop_uni_list_front(&(info->sub_args));
	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next)
		mx_pop_info_l_front(&(info->info_l));
}

void mx_arg_files(t_info *info) { // обробка аргумента, що є файлом
	for (int i = 0; i < info->argc; i++) {
		if (info->where_what[i] == 2) {
			info->num_of_sub++;
			mx_push_uni_list_back(&(info->sub_args), info->argv[i], NULL, 0);
		}
	}
	mx_sort_uni_list(info->sub_args);
	if (info->flags_exist)
		mx_work_with_flags(info);
	mx_print_arg(info, 0);
	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next)
		mx_pop_uni_list_front(&(info->sub_args));
	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next)
		mx_pop_info_l_front(&(info->info_l));
}

void mx_arg_folders(t_info *info) { // обробка аргумента, що є папкою
	for (int i = 0; i < info->argc; i++) {
		if (info->where_what[i] == 3) {
			if (info->flag_R)
				mx_flag_R(info, info->argv[i]);
			else
				mx_work_with_one_arg(info, info->argv[i], 1);
		}
	}
}

void mx_work_with_args(t_info *info) {
	mx_arg_not_exist(info);
	if (info->flags_exist)
		mx_take_flags(info);
	if (info->file_exist || info->folder_exist) {
		if (info->file_exist)
			mx_arg_files(info);
		if (info->folder_exist)
			mx_arg_folders(info);
	}
	else { // якщо не дано ні файлу пі папки
		default_args(info);
		if (info->flag_R)
			mx_flag_R(info, info->argv[0]);
		else
			mx_work_with_one_arg(info, info->argv[0], 1);
	}
}

static void default_args(t_info *info) {
	char **all_elems = (char **)malloc(sizeof(char *) * 2);
	
	all_elems[0] = ".";
	all_elems[1] = NULL;
	info->argc = 1;
	info->argv = all_elems;
}
