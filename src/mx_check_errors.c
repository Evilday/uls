#include "uls.h"

static bool check_argv_2(t_info *info, DIR *f, struct dirent *d, int i);
static bool check_argv_3(t_info *info, struct dirent *d, int i);

char *mx_up_to_one(char *str) {
	if (str) {
		int pos = mx_strlen(str) - 1;

		while (pos > 0 && str[pos] != '/')
			pos--;
		return mx_strndup(str, pos);
	}
	else
		return NULL;
}

bool mx_check_argv(t_info *info, int i) {
	DIR *f = NULL;
	struct dirent *d = NULL;

	if ((f = opendir(info->argv[i]))) {
		closedir(f);
		info->folder_exist = 1;
		info->where_what[i] = 3;
		return 1;
	}
	else
		return check_argv_2(info, f, d, i);
	return 0;
}

bool mx_check_flags(t_info *info, int i) {
	char all_flags[23] = "laARGh@T1CrtucSmfpFgnd\0";

	if (info->argv[i][0] == '-' && info->argv[i][1]) {
		if (info->argv[i][1] == '-' && !info->argv[i][2]) {
			info->where_what[i] = 4;
			return 0;
		}
		info->flags_exist = 1;
		for (int j = 1; info->argv[i][j]; j++) {
			if (!mx_strchr(all_flags, info->argv[i][j])) {
				mx_invalid_usage(info->argv[i][j]);
				exit(1);
			}
		}
		info->where_what[i] = 1;
		return 1;
	}
	else
		mx_check_argv(info, i);
	return 0;
}

static bool check_argv_2(t_info *info, DIR *f, struct dirent *d, int i) {
	char *file = mx_up_to_one(info->argv[i]);
	bool res = 0;

	if ((f = opendir(file))) {
		while ((d = readdir(f)))
			if (!mx_strcmp(d->d_name, info->argv[i] + (mx_strlen(file) + 1))) {
				if (d->d_type != 4) {
					info->file_exist = 1;
					info->where_what[i] = 2;
					res = 1;
				}
				break;
			}
		closedir(f);
	}
	else
		res = check_argv_3(info, d, i);
	free(file);
	return res;
}

static bool check_argv_3(t_info *info, struct dirent *d, int i) {
	DIR *f = opendir(".");

	while((d = readdir(f)))
		if (!mx_strcmp(d->d_name, info->argv[i])) {
			info->file_exist = 1;
			info->where_what[i] = 2;
			closedir(f);
			return 1;
		}
	closedir(f);
	return 0;
}
