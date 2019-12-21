#include "uls.h"

void mx_rotate(t_info *info) {
	int num_args = info->num_of_sub - 1;

	for (int j = 0; j < num_args; j++, num_args--) {
		mx_swap_uni_list(info, j, num_args);
		if (info->print_flag == 'l')
			mx_swap_l(info, j, num_args);
	}
}
