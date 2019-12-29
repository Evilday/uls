#include "uls.h"

void mx_clear_all(t_info *info) {
	while (info->info_l)
		mx_pop_info_l_front(&(info->info_l));
}
