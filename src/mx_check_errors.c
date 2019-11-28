#include "uls.h"

bool mx_check_flags(t_info *info, int i) {
	//printf("start\n");

	char all_flags[2] = "l\0";

	if (info->argv[i][0] == '-') {
		if (info->argv[i][1] == '-' && !info->argv[i][2]) {
			//printf("found --\n");
			return 0;
		}
		info->flags_exist = 1;
		for (int j = 1; info->argv[i][j]; j++) {
			if (!mx_strchr(all_flags, info->argv[i][j])) {
				mx_invalid_usage();
				exit(0);
			}
		}
		return 1;
	}
	else {
		printf("go to argv\n");
		mx_check_argv(info, i);
	}
	return 0;
}

// bool mx_check_argv(t_info *info, int i) {
// 	DIR *f = opendir(".");
// 	struct dirent *d;

// 	while((d = readdir(f))) {
// 		if (!mx_strcmp(d->d_name, info->argv[i])) {
// 			info->args_exist = 1;
// 			closedir(f);
// 			return 1;
// 		}
// 	}
// 	closedir(f);
// 	info->exist[i] = 0;
// 	return 0;
// }

static char *up_to_one(char *str) {
	int pos = mx_strlen(str) - 1;

	while (str[pos] != *str && str[pos] != '/')
		pos--;
	return mx_strndup(str, pos);
}

static bool else_check_argv(char *arg, char *file, DIR *f, struct dirent *d) {
	if ((f = opendir(file))) {
		while((d = readdir(f)))
			if (!mx_strcmp(d->d_name, arg + mx_strlen(file) + 1)) {
				closedir(f);
				return 1;
			}
	}
	else {
		f = opendir(".");
		while((d = readdir(f)))
			if (!mx_strcmp(d->d_name, arg)) {
				closedir(f);
				return 1;
			}
	}
	return 0;
}

bool mx_check_argv(t_info *info, int i) {
	DIR *f;
	struct dirent *d;
	char *file;

	if ((f = opendir(info->argv[i]))) {
		info->args_exist = 1;
		closedir(f);
		return 1;
	}
	else {
		file = up_to_one(info->argv[i]);
		if (else_check_argv(info->argv[i], file, f, d)) {
			free(file);
			info->args_exist = 1;
			return 1;
		}
		free(file);
	}
	info->exist[i] = 0;
	return 0;
}
