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
						|| info->argv[i][j] == 'S')
					info->top_flag = info->argv[i][j];
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
	if (info->top_flag == 'l') {
		mx_l_flag(info);
	}
	else if (info->top_flag == '1') {
		//
	}
}

static void mx_take_flags_2(t_info *info, bool *our_flags) {
	if (our_flags[1])
		info->flag_a = 1;
	else if (our_flags[2])
		info->flag_A = 1;
	else if (our_flags[3])
		info->flag_R = 1;
}
