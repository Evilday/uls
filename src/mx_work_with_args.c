#include "uls.h"

void mx_sort_args(t_info *info) {
	char *temp_str;
	int temp_id;
	for (int i = 0; info->argv[i]; i++) {
		for (int j = 0; info->argv[j + 1 + i]; j++) {
			if (mx_strcmp(info->argv[j], info->argv[j + 1]) > 0) {
				temp_str = info->argv[j];
				temp_id = info->exist[j];
				info->argv[j] = info->argv[j + 1];
				info->exist[j] = info->exist[j + 1];
				info->argv[j + 1] = temp_str;
				info->exist[j + 1] = temp_id;
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
		}
	}
	closedir(f);
	info->argc = num_of_elems;
	info->argv = all_elems;
}

void mx_work_with_args(t_info *info) {
	if (info->args_exist)
		printf("ARGS exist\n");
	else
		default_args(info);
}
