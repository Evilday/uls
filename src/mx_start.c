#include "uls.h"

static bool check_basic_errors(t_info *info) {
	bool flags = 1;
	for (int i = 0; i < info->argc; i++) {
		if (flags) {
			if (!mx_check_flags(info, i))
				flags = 0;
		}
		else {
			mx_check_argv(info, i);
		}
	}
	return 1;
}

void mx_start(t_info *info) {
	if (check_basic_errors(info)) {
		// just for look
		// printf("======Info flags and args=======\n");
		// printf("INFO = flags = %d , arg = %d\n", info->flags_exist, info->args_exist);
		// for (int i = 0; i < info->argc; i++)
		// 	printf("file/folder = %d\n", info->where_what[i]);
		// printf("================================\n");
		// End
		mx_sort_args(info);
		mx_work_with_args(info);
	}
}
