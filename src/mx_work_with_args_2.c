#include "uls.h"

static bool check_sub_argv(t_info *info, int i, DIR *f, struct dirent *d) {
	int num_of_sub = 0;

	if ((f = opendir(info->argv[i]))) {
		if (info->flag_a || info->flag_A)
			mx_look_sub_argv_2(info, i, f, d);
		else {
			while ((d = readdir(f)))
				if (d->d_name[0] != '.') {
					mx_push_uni_list_back(&(info->sub_args), d->d_name, info->argv[i]);
					++num_of_sub;
				}
			info->num_of_sub = num_of_sub;
		}
		closedir(f);
		return 1;
	}
	return 0;
}

static bool else_look_sub_argv(t_info *info, char *file, int i) {
	DIR *f;
	struct dirent *d;
	int num_of_sub = 0;

	if ((f = opendir(file))) {
		while((d = readdir(f)))
			if (d->d_name[0] != '.') {
				mx_push_uni_list_back(&(info->sub_args), d->d_name, file);
				++num_of_sub;
			}
			closedir(f);
			info->num_of_sub = num_of_sub;
			return 1;
	}
	else {
		mx_push_uni_list_back(&(info->sub_args), info->argv[i], "./");
		info->num_of_sub = 1;
		return 1;
	}
	return 0;
}

bool mx_look_sub_argv(t_info *info, int i) {
	DIR *f = NULL;
	struct dirent *d = NULL;
	char *file;

	if (check_sub_argv(info, i, f, d)) {
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
