#include "uls.h"

static void mx_take_flags_2(t_info *info, bool *our_flags);

void mx_l_flag(t_info *info) {
	info->total_blocks_l = 0;
	mx_l_permissions(info);
	mx_group_size_for_l(info);
	mx_date_time_for_l(info);
}

void mx_take_flags(t_info *info) {
	bool *our_flags = (bool *)malloc(17);
	char all_flags[17] = "laARGh@eT1CrtucS\0";
	int i;

	for (i = 0; i < 17; i++)
		our_flags[i] = 0;
	for (i = 0; i < info->argc; i++) {
		if (info->where_what[i] == 1)
			for (int j = 1; info->argv[i][j]; j++) {
				if (info->argv[i][j] == 'l' || info->argv[i][j] == '1' 
						|| info->argv[i][j] == 'C')
					info->print_flag = info->argv[i][j];
				else if (info->argv[i][j] == 't')
					info->sort_flag = info->argv[i][j];
				else
					for (int p = 0; all_flags[p]; p++)
						if (all_flags[p] == info->argv[i][j])
							our_flags[p] = 1;
			}
	}
	mx_take_flags_2(info, our_flags);
	free(our_flags);
}

void mx_work_with_flags(t_info *info) {
	if (info->print_flag == 'l') {
		mx_l_flag(info);
	}
	else if (info->print_flag == '1') {
		//
	}
	if (info->sort_flag != '0')
		mx_sort_with_flags(info);
	if (info->flag_r)
		mx_rotate(info);
}

static void mx_take_flags_2(t_info *info, bool *our_flags) {
	if (our_flags[1])
		info->flag_a = 1;
	if (our_flags[2])
		info->flag_A = 1;
	if (our_flags[3])
		info->flag_R = 1;
	if (our_flags[11])
		info->flag_r = 1;
}
