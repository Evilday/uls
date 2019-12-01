#include "uls.h"

void mx_look_sub_argv_2(t_info *info, int i, DIR *f, struct dirent *d) {
	while ((d = readdir(f))) {
		if (info->flag_a) {
			mx_push_uni_list_back(&(info->sub_args), d->d_name, info->argv[i]);
		}
		else if (info->flag_A && mx_strcmp(d->d_name, ".") 
			&& mx_strcmp(d->d_name, "..")) {
			mx_push_uni_list_back(&(info->sub_args), d->d_name, info->argv[i]);
		}
		else if (d->d_name[0] != '.')
			mx_push_uni_list_back(&(info->sub_args), d->d_name, info->argv[i]);
	}
}
