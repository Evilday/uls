#include "uls.h"

static unsigned long *save_time(t_info *info);

void mx_sort_with_flags(t_info *info) {
	if (info->sort_flag == 't')
		mx_flag_t(info);
	else if (info->sort_flag == 'S')
		mx_flag_S(info);
}

void mx_flag_t(t_info *info) {
	int elem = 0;
	unsigned long *time_all = save_time(info);
	unsigned long temp;

	for (int i = 1; i < info->num_of_sub; i++) {
		elem = 0;
		for (int j = 0; j < info->num_of_sub - i; j++) {
			if (time_all[j] > time_all[j + 1]) {
				mx_swap_uni_list(info, elem, elem + 1);
				if (info->print_flag == 'l')
					mx_swap_l(info, elem, elem + 1);
				temp = time_all[j];
				time_all[j] = time_all[j + 1];
				time_all[j + 1] = temp;
			}
			elem++;
		}
	}
	free(time_all);
}

static unsigned long *save_time(t_info *info) {
	unsigned long *time_all = (unsigned long 
		*)malloc(sizeof(unsigned long) * info->num_of_sub);
	struct stat time_struct;
	char *arg;
	int i = 0;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next, i++) {
		arg = mx_strjoin(info->path, tmp->data);
		lstat(arg, &time_struct);
		if (info->time_flag == 'u')
			time_all[i] = time(0) - time_struct.st_atime;
		else if (info->time_flag == 'c')
			time_all[i] = time(0) - time_struct.st_ctime;
		else
			time_all[i] = time(0) - time_struct.st_ctime;
		free(arg);
	}
	return time_all;
}
