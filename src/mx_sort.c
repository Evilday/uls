#include "uls.h"

static unsigned long *save_time(t_info *info);

void mx_sort_with_flags(t_info *info) {
	if (info->sort_flag == 't')
		mx_flag_t(info);
	else if (info->sort_flag == 'S')
		mx_flag_S(info);
}

void mx_sort_args(t_info *info) {
	char *temp_str;
	int temp_id;
	for (int i = 0; info->argv[i]; i++) {
		for (int j = 0; info->argv[j + 1 + i]; j++) {
			if (mx_strcmp(info->argv[j], info->argv[j + 1]) > 0) {
				temp_str = info->argv[j];
				temp_id = info->where_what[j];
				info->argv[j] = info->argv[j + 1];
				info->where_what[j] = info->where_what[j + 1];
				info->argv[j + 1] = temp_str;
				info->where_what[j + 1] = temp_id;
			}
		}
	}
}

void mx_sort_uni_list(t_info *info, t_uni_list *lst) {
	if (info->sort_flag == '0') {
		bool temp;

		if (lst)
			for (t_uni_list *temp1 = lst; temp1; temp1 = temp1->next)
				for (t_uni_list *temp2 = lst; temp2->next; temp2 = temp2->next)
					if(mx_strcmp(temp2->data, temp2->next->data) > 0) {
						mx_swap_str(&temp2->data, &temp2->next->data);
						temp = temp2->folder;
						temp2->folder = temp2->next->folder;
						temp2->next->folder = temp;
					}
	}
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
