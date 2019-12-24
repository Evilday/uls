#include "uls.h"

static void sort_with_flag_S(t_info *info);
static void take_size(t_info *info);
static void take_permissions_and_size(t_info *info);

void mx_flag_S(t_info *info) {
	if (info->print_flag != 'l')
		take_permissions_and_size(info);
	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next)
		if (tmp->access[0] == 'b' || tmp->access[0] == 'c')
			return;
	sort_with_flag_S(info);
}

static void sort_with_flag_S(t_info *info) {
	int elem = 0;
	int rec = 1;

	if (info->num_of_sub > 1) {
		while (rec) {
			rec = 0;
			elem = 0;
			for (t_info_l *tmp2 = info->info_l; tmp2->next; tmp2 = tmp2->next) {
				if (mx_atoi(tmp2->size) < mx_atoi(tmp2->next->size)) {
					mx_swap_uni_list(info, elem, elem + 1);
					mx_swap_l(info, elem, elem + 1);
					rec = 1;
					break;
				}
				elem++;
			}
		}
	}
	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		mx_printstr(tmp->data);
		mx_printchar(' ');
	}
	mx_printchar('\n');
	for (t_info_l *tmp2 = info->info_l; tmp2->next; tmp2 = tmp2->next) {
		mx_printstr(tmp2->size);
		mx_printchar(' ');
	}
}

static void take_size(t_info *info) {
	char *theOne;
	struct stat buff;
	t_uni_list *tmp2 = info->sub_args;

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
		theOne = mx_strjoin(info->path, tmp2->data);

		lstat(theOne, &buff);
		tmp->size = mx_itoa(buff.st_size);
		tmp2 = tmp2->next;
	}
}

static void take_permissions_and_size(t_info *info) {
	struct stat buff;
	char *arg;
	char *file_type;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		arg = mx_strjoin(info->path, tmp->data);
		lstat(arg, &buff);
		file_type = mx_strnew(1);
		file_type[0] = mx_get_type(buff);
		mx_push_info_l_back(&(info->info_l), file_type);
		free(arg);
	}
	take_size(info);
}
