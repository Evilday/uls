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

static void default_args(t_info *info) {
	int num_of_elems = 0;
	char **all_elems;
	DIR *f = opendir(".");
	struct dirent *d = readdir(f);

	while ((d = readdir(f)))
		num_of_elems++;
	closedir(f);
	f = opendir(".");
	if (num_of_elems > 0) {
		all_elems = (char **)malloc(sizeof(char *) * (num_of_elems + 1));
		all_elems[num_of_elems] = NULL;
		for (int i = 0; i < num_of_elems; i++) {
			d = readdir(f);
			all_elems[i] = mx_strdup(d->d_name);
			where_what[i] = 2;
		}
	}
	closedir(f);
	info->argc = num_of_elems;
	info->argv = all_elems;
}

static bool else_look_sub_argv(t_info *info, char *file, int i) {
	DIR *f;
	struct dirent *d;

	if ((f = opendir(file))) {
		while((d = readdir(f)))
			mx_push_uni_list_back(&(info->sub_args), d->d_name);
			closedir(f);
			return 1;
	}
	else {
		mx_push_uni_list_back(&(info->sub_args), info->argv[i]);
		return 1;
	}
	return 0;
}

bool mx_look_sub_argv(t_info *info, int i) {
	DIR *f;
	struct dirent *d;
	char *file;

	if ((f = opendir(info->argv[i]))) {
		while ((d = readdir(f))) {
			mx_push_uni_list_back(&(info->sub_args), d->d_name);
		}
		closedir(f);
		return 1;
	}
	else {
		file = mx_up_to_one(info->argv[i]);
		if (else_look_sub_argv(info, file, i)) {
			free(file);
			return 1;
		}
		free(file);
	}
	return 0;
}

void mx_print_arg(t_info *info) {
	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		mx_printstr(tmp->data);
		mx_printchar('\n');
	}
	mx_printchar('\n');
}

void mx_file_or_folder() {
	
}

void mx_work_with_one_arg(t_info *info, int i) {
	mx_look_sub_argv(info, i);
	if (info->flags_exist)
		mx_work_with_flags(info);
	mx_print_arg(info);
	// for (t_uni_list *tmp = info->access; tmp; tmp = tmp->next)
	// 	printf("ARG: %s\n", tmp->data);
	// for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
	// 	mx_pop_uni_list_front(&(info->sub_args));
	// }
	// for (t_uni_list *tmp = info->access; tmp; tmp = tmp->next) {
	// 	mx_pop_uni_list_front(&(info->access));
	// }
	printf("\n");
}

void mx_work_with_args(t_info *info) {
	if (info->flags_exist)
		mx_take_flags(info);
	if (info->args_exist)
		printf("Args exist !\n");
	else
		default_args(info);
	for (int i = 0; i < info->argc; i++) {
		if (info->where_what[i] == 2) {
			mx_work_with_one_arg(info, i);
		}
	}
}
