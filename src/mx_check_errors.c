#include "uls.h"

static bool else_check_argv(char *arg, char *file, DIR *f, struct dirent *d);

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
	char *file;

	if ((f = opendir(info->argv[i]))) { // намагаємося вікрити аргумент
		closedir(f);
		info->folder_exist = 1;
		info->where_what[i] = 3;
		return 1;
	}
	else {
		file = mx_up_to_one(info->argv[i]); // обрізаємо уточнення, що це файл
		f = opendir(file);
		if (f)
			while ((d = readdir(f)))
				if (!mx_strcmp(d->d_name, info->argv[i] + (mx_strlen(file) + 1))) {
					if (d->d_type != 4)
						if (else_check_argv(info->argv[i], file, f, d)) {
							free(file);
							info->file_exist = 1;
							info->where_what[i] = 2;
							return 1;
						}
					free(file);
					break;
				}
	}
	return 0;
}

bool mx_check_flags(t_info *info, int i) {
	char all_flags[17] = "laARGh@eT1CrtucS\0";

	if (info->argv[i][0] == '-' && info->argv[i][1]) {
		if (info->argv[i][1] == '-' && !info->argv[i][2]) {
			info->where_what[i] = 4;
			return 0;
		}
		info->flags_exist = 1;
		for (int j = 1; info->argv[i][j]; j++) {
			if (!mx_strchr(all_flags, info->argv[i][j])) {
				mx_invalid_usage();
				exit(0);
			}
		}
		info->where_what[i] = 1;
		return 1;
	}
	else
		mx_check_argv(info, i);
	return 0;
}

static bool else_check_argv(char *arg, char *file, DIR *f, struct dirent *d) {
	if ((f = opendir(file))) { // намагаємося відкрити без уточнення, що це файл
		while((d = readdir(f))) {
			if (!mx_strcmp(d->d_name, arg + mx_strlen(file) + 1)) {
				closedir(f);
				return 1;
			}
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
	closedir(f);
	return 0;
}
