#include "uls.h"

void mx_on_off_flags(t_info *info) {
	if (info->flag_f) {
		if (info->print_flag == 'l')
			info->print_flag = '0';
		if (info->sort_flag == 't' || info->sort_flag == 'S')
			info->sort_flag = '0';
		info->flag_r = 0;
		info->flag_a = 1;
	}
	if (info->print_flag != 'l')
		info->flag_h = 0;
	if (!isatty(1)) {
		if (info->print_flag == '0' || info->print_flag == 'C')
			info->print_flag = '1';
		if (info->flag_G)
			info->flag_G = 0;
	}
	if (info->flag_d)
		info->flag_a = 1;
}
