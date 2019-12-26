#include "uls.h"

static void mx_sort_args_flag_f(t_info *info);
static void mx_sort_uni_list_flag_f(t_uni_list *lst);
static int alpha_num_diff(char *s1, char *s2);

void mx_sort_args(t_info *info) {
	if (!info->flag_f) {
		char *temp_str;
		int temp_id;

		for (int i = 0; info->argv[i]; i++)
			for (int j = 0; info->argv[j + 1 + i]; j++)
				if (mx_strcmp(info->argv[j], info->argv[j + 1]) > 0) {
					temp_str = info->argv[j];
					temp_id = info->where_what[j];
					info->argv[j] = info->argv[j + 1];
					info->where_what[j] = info->where_what[j + 1];
					info->argv[j + 1] = temp_str;
					info->where_what[j + 1] = temp_id;
				}
	}
	else
		mx_sort_args_flag_f(info);
}

void mx_sort_uni_list(t_info *info, t_uni_list *lst) {
	if (info->flag_f)
		mx_sort_uni_list_flag_f(lst);
	else if (info->sort_flag == '0') {
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

static void mx_sort_args_flag_f(t_info *info) {
	char *temp_str;
	int temp_id;

	for (int i = 0; info->argv[i]; i++) {
		for (int j = 0; info->argv[j + 1 + i]; j++) {
			if (alpha_num_diff(info->argv[j], info->argv[j + 1]) > 0) {
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

static void mx_sort_uni_list_flag_f(t_uni_list *lst) {
	bool temp;

	if (lst)
		for (t_uni_list *temp1 = lst; temp1; temp1 = temp1->next)
			for (t_uni_list *temp2 = lst; temp2->next; temp2 = temp2->next)
				if(alpha_num_diff(temp2->data, temp2->next->data) > 0) {
					mx_swap_str(&temp2->data, &temp2->next->data);
					temp = temp2->folder;
					temp2->folder = temp2->next->folder;
					temp2->next->folder = temp;
				}
}

static int alpha_num_diff(char *s1, char *s2) {
	int n1;
	int n2;

	while (*s1 || *s2) {
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}
	n1 = *s1 >= 65 && *s1 <= 90 ? *s1 - 65 : *s1 - 97;
	n2 = *s2 >= 65 && *s2 <= 90 ? *s2 - 65 : *s2 - 97;
	return n1 - n2;
}
