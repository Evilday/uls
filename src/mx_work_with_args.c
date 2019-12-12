#include "uls.h"

// void mx_check_folder(t_info *info) {
// 	if (info) {}

// 	DIR *f;
// 	struct dirent *dr;
// 	f = opendir(".");
// 	while ((dr = readdir(f))) {
// 		printf("d_ino = %d    %s\n", dr->d_type, dr->d_name);
// 	}
// }

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
	bool temp;

	if (lst)
		for (t_uni_list *temp1 = lst; temp1; temp1 = temp1->next)
			for (t_uni_list *temp2 = lst; temp2->next; temp2 = temp2->next)
				if(mx_strcmp(temp2->data, temp2->next->data) > 0) {
					mx_swap_str(&temp2->data, &temp2->next->data);
					mx_swap_str(&temp2->path, &temp2->next->path);
					temp = temp2->folder;
					temp2->folder = temp2->next->folder;
					temp2->next->folder = temp;
				}
}

static void default_args(t_info *info) {
	char **all_elems = (char **)malloc(sizeof(char *) * 2);
	all_elems[0] = ".";
	all_elems[1] = NULL;
	info->argc = 1;
	info->argv = all_elems;
}

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

void mx_work_with_args(t_info *info) {
	mx_arg_not_exist(info);
	if (info->flags_exist)
		mx_take_flags(info);
	if (info->args_exist) { // спочатку на друк всі файли, а тоді всі папки
		for (int i = 0; i < info->argc; i++) {
			if (info->where_what[i] == 2)
				mx_work_with_one_arg(info, info->argv[i], 0); // обробка аргумента, що є файлом
		}
		for (int i = 0; i < info->argc; i++) {
			if (info->where_what[i] == 3)
				mx_work_with_one_arg(info, info->argv[i], 1); // обробка аргумента, що є папкою
		}
	}
	else { // якщо не дано ні файлу пі папки
		default_args(info);
		mx_work_with_one_arg(info, info->argv[0], 3);
	}
}
