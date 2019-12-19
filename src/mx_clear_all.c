#include "uls.h"

void mx_clear_all(t_info *info) {
	if (info->print_flag == 'l' || info->sort_flag == 'S') {
		for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next)
			mx_pop_info_l_front(&(info->info_l));
		free(info->info_l);
	}
}
