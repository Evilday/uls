#include "uls.h"

static bool check_sub_argv(t_info *info, char *arg, t_uni_list *where_to_save);
static bool else_look_sub_argv(t_info *info, char *arg, char *file, t_uni_list *where_to_save);

bool mx_look_sub_argv(t_info *info, char *arg, t_uni_list *where_to_save) {
	char *file;

	if (malloc_size(info->path))
		mx_strdel(&info->path);
	if (check_sub_argv(info, arg, where_to_save)) { // спроба відкрити аргумент
		return 1;
	}
	else {
		file = mx_up_to_one(arg);
		if (else_look_sub_argv(info, arg, file, where_to_save)) {
			free(file);
			return 1;
		}
		free(file);
	}
	return 0;
}

static bool check_sub_argv(t_info *info, char *arg, t_uni_list *where_to_save) {
	int num_of_sub = 0;
	struct dirent *d = NULL;
	DIR *f = NULL;
	char *path = mx_strjoin(arg, "/");

	if ((f = opendir(arg))) { // намагаємося відкрити агрумент
		info->path = mx_strdup(arg);
		if (info->flag_a || info->flag_A) // якщо є флаги А або а, то читаємо з ними 
			mx_look_sub_argv_2(info, arg, f, where_to_save);
		else {
			while ((d = readdir(f)))
				if (d->d_name[0] != '.') {
					mx_push_uni_list_back(info, &(where_to_save), mx_strjoin(path, d->d_name), d->d_type);
					++num_of_sub;
				}
			info->num_of_sub = num_of_sub;
		}
		closedir(f);
		free(path);
		return 1;
	}
	free(path);
	return 0;
}

static bool else_look_sub_argv(t_info *info, char *arg, char *file, t_uni_list *where_to_save) {
	DIR *f;
	struct dirent *d;
	int num_of_sub = 0;

	if ((f = opendir(file))) { // намагаємося відкрити аргумент без закінчення (src/main.c = src/)
		while((d = readdir(f))) {
			if (!mx_strcmp(d->d_name, arg + mx_strlen(file) + 1)) {
				mx_push_uni_list_back(info, &(where_to_save), arg, d->d_type);
				++num_of_sub;
			}
		}
			closedir(f);
			info->num_of_sub = num_of_sub;
			info->path = mx_strdup(file);
			return 1;
	}
	else {
		f = opendir("."); // шукаємо файл в папці де ми знаходимося
		while((d = readdir(f)))
			if (!mx_strcmp(d->d_name, arg)) {
				mx_push_uni_list_back(info, &(where_to_save), arg, d->d_type);
				info->path = mx_strdup(".");
				info->num_of_sub = 1;
			}
		closedir(f);
		return 1;
	}
	return 0;
}
