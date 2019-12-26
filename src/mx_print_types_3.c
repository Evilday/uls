#include "uls.h"

void mx_choose_print_action(t_info *info, t_uni_list *tmp) {
	if (info->p_F_flag != '0')
		mx_flag_p_or_F(info, tmp);
	else if (info->flag_G)
		mx_print_color(info, tmp);
	else
		mx_printstr(tmp->data);
}

void mx_print_l_2(t_info_l *tmp, t_tabs_l *tmp3) {
	mx_printstr(tmp->group_owner);
	mx_print_tabs(tmp3->l_group_owner - mx_strlen(tmp->group_owner));
	mx_print_tabs(!tmp->minor_major ? tmp3->l_size
		- mx_strlen(tmp->size) + 2 : 2);
	mx_printstr(tmp->size);
	mx_print_tabs(1);
	mx_printstr(tmp->time_upd);
	mx_print_tabs(tmp3->l_time_upd - mx_strlen(tmp->time_upd) + 1);
}
