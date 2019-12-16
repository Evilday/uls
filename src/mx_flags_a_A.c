#include "uls.h"

void mx_look_sub_argv_2(t_info *info, char *arg, DIR *f, t_uni_list *where_to_save) {
	int num_sub_args = 0;
	struct dirent *d = NULL;
	printf("mx_look_sub_argv_2 ARG = %s\n", arg);

	while ((d = readdir(f))) {
		if (info->flag_a) {
			mx_push_uni_list_back(info, &(where_to_save), d->d_name, d->d_type);
			++num_sub_args;
		}
		else if (info->flag_A && mx_strcmp(d->d_name, ".") 
			&& mx_strcmp(d->d_name, "..")) {
			mx_push_uni_list_back(info, &(where_to_save), d->d_name, d->d_type);
			++num_sub_args;
		}
	}
	info->num_of_sub = num_sub_args;
}
