#include "uls.h"

void mx_rotate(t_info *info) {
	int num_args = info->num_of_sub;

	for (int i = 1; i < num_args; i++) {
		for (int j = 0; j < num_args - i; j++) {
			mx_swap_uni_list(info, j, j + 1);
			if (info->print_flag == 'l')
				mx_swap_l(info, j, j + 1);
		}
	}	
}
