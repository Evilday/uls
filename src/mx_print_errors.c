#include "uls.h"

// Errors
void mx_invalid_usage() {
	mx_printerr(INVALID_USAGE);
	mx_printerr("\n");
}

void mx_arg_not_exist(t_info *info) {
	bool errors = 0;

	for (int i = 0; i < info->argc; i++)
		if (!info->where_what[i]) {
			mx_is_allowed(info->argv[i]);
			errors = 1;
		}
	if (errors && !info->file_exist && !info->folder_exist)
		exit(0);
}

void mx_is_allowed(char *path) {
	char *full_error;

	while (mx_strchr(path, '/') != 0) {
		path = mx_strchr(path, '/');
		path++;
	}
	full_error = mx_strnew(1);
	full_error = mx_strjoin(full_error, "uls: ");
	full_error = mx_strjoin(full_error, path);
	perror(full_error);
	free(full_error);
}
