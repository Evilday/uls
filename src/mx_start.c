#include "uls.h"

static bool check_basic_errors(t_info *info);

void mx_start(t_info *info) {
	if (check_basic_errors(info)) {
		for (int i = 0; i < info->argc; i++)
			if (info->where_what[i] == 2 || info->where_what[i] == 3 
				|| info->where_what[i] == 0)
				info->num_of_arg++;
		mx_sort_args(info);
		mx_work_with_args(info);
	}
}

static bool check_basic_errors(t_info *info) {
	bool flags = 1;

	for (int i = 0; i < info->argc; i++) {
		if (flags) {
			if (!mx_check_flags(info, i))
				flags = 0;
		}
		else
			mx_check_argv(info, i);
	}
	return 1;
}
