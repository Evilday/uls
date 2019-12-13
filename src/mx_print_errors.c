#include "uls.h"

// Errors
void mx_invalid_usage() {
	mx_printerr(INVALID_USAGE);
	mx_printerr("\n");
}

void mx_arg_not_exist(t_info *info) {
	for (int i = 0; i < info->argc; i++)
		if (!info->where_what[i]) {
			mx_printerr("uls: ");
			mx_printerr(info->argv[i]);
			mx_printerr(": No such file or directory");
			mx_printerr("\n");
		}
}
