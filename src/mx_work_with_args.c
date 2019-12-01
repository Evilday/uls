#include "uls.h"

void mx_sort_args(t_info *info) {
	char *temp_str;
	int temp_id;
	for (int i = 0; info->argv[i]; i++) {
		for (int j = 0; info->argv[j + 1 + i]; j++) {
			if (mx_strcmp(info->argv[j], info->argv[j + 1]) > 0) {
				temp_str = info->argv[j];
				temp_id = info->where_what[j];
				info->argv[j] = info->argv[j + 1];
				info->where_what[j] = info->where_what[j + 1];
				info->argv[j + 1] = temp_str;
				info->where_what[j + 1] = temp_id;
			}
		}
	}
}

void mx_sort_uni_list(t_uni_list *lst) {
	char *temp;

	if (lst)
		for (t_uni_list *temp1 = lst; temp1; temp1 = temp1->next)
			for (t_uni_list *temp2 = lst; temp2->next; temp2 = temp2->next)
				if(mx_strcmp(temp2->data, temp2->next->data) > 0) {
					temp = temp2->data;
					temp2->data = temp2->next->data;
					temp2->next->data = temp;
					temp = temp2->path;
					temp2->path = temp2->next->path;
					temp2->next->path = temp;
				}
}

static void default_args(t_info *info) {
	// int num_of_elems = 0;
	// char **all_elems;
	// DIR *f = opendir(".");
	// struct dirent *d = readdir(f);
	// int i = 0;

	// while ((d = readdir(f)))
	// 	if (d->d_name[0] != '.')
	// 		num_of_elems++;
	// closedir(f);
	// f = opendir(".");
	// if (num_of_elems > 0) {
	// 	all_elems = (char **)malloc(sizeof(char *) * (num_of_elems + 1));
	// 	all_elems[num_of_elems] = NULL;
	// 	while ((d = readdir(f))) {
	// 		if (d->d_name[0] != '.') {
	// 			all_elems[i] = mx_strdup(d->d_name);
	// 			info->where_what[i++] = 2;
	// 		}
	// 	}
	// }
	// closedir(f);
	char **all_elems = (char **)malloc(sizeof(char *) * 2);
	all_elems[0] = ".";
	all_elems[1] = NULL;
	info->argc = 1;
	info->argv = all_elems;
}

void mx_work_with_one_arg(t_info *info, int i) {
	mx_look_sub_argv(info, i);
	mx_sort_uni_list(info->sub_args);
	if (info->flags_exist)
		mx_work_with_flags(info);
	mx_print_arg(info);
	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next)
		mx_pop_uni_list_front(&(info->sub_args));
	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next)
		mx_pop_info_l_front(&(info->info_l));
}

void mx_work_with_args(t_info *info) {
	mx_arg_not_exist(info);
	if (info->flags_exist)
		mx_take_flags(info);
	if (info->args_exist) {
		// printf("Args exist !\n");
		for (int i = 0; i < info->argc; i++) {
			if (info->where_what[i] == 2) {
				mx_work_with_one_arg(info, i);
			}
		}
	}
	else {
		for (int i = 0; i < info->argc; i++)
			if (!info->where_what[i])
				return;
		default_args(info);
		mx_work_with_one_arg(info, 0);
	}
}
