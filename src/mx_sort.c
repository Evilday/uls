#include "uls.h"

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

void mx_sort_uni_list(t_uni_list *lst) {
	bool temp;

	if (lst)
		for (t_uni_list *temp1 = lst; temp1; temp1 = temp1->next)
			for (t_uni_list *temp2 = lst; temp2->next; temp2 = temp2->next)
				if(mx_strcmp(temp2->data, temp2->next->data) > 0) {
					mx_swap_str(&temp2->data, &temp2->next->data);
					mx_swap_str(&temp2->path, &temp2->next->path);
					temp = temp2->folder;
					temp2->folder = temp2->next->folder;
					temp2->next->folder = temp;
				}
}
