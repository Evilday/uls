#include "uls.h"
// print_l
void mx_count_tabs_l(t_info *info) {
	t_tabs_l *tabs_l = (t_tabs_l *)malloc(sizeof(t_tabs_l));
	tabs_l->l_nlink = tabs_l->l_login = tabs_l->l_group_owner
	= tabs_l->l_sym_num = tabs_l->l_time_upd = 0;

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
		if (mx_strlen(tmp->nlink) > tabs_l->l_nlink)
			tabs_l->l_nlink = mx_strlen(tmp->nlink);
		if (mx_strlen(tmp->login) > tabs_l->l_login)
			tabs_l->l_login = mx_strlen(tmp->login);
		if (mx_strlen(tmp->group_owner) > tabs_l->l_group_owner)
			tabs_l->l_group_owner = mx_strlen(tmp->group_owner);
		if (mx_strlen(tmp->sym_num) > tabs_l->l_sym_num)
			tabs_l->l_sym_num = mx_strlen(tmp->sym_num);
		if (mx_strlen(tmp->time_upd) > tabs_l->l_time_upd)
			tabs_l->l_time_upd = mx_strlen(tmp->time_upd);
	}
	info->tabs_l = tabs_l;
}

void mx_print_l(t_info *info) {
	t_uni_list *t2 = info->sub_args;
	t_tabs_l *tmp3 = info->tabs_l;

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next, t2 = t2->next) {
		mx_printstr(tmp->access);
		mx_print_tabs(tmp3->l_nlink - mx_strlen(tmp->nlink));
		mx_printstr(tmp->nlink);
		mx_print_tabs(1);
		mx_printstr(tmp->login);
		mx_print_tabs(tmp3->l_login - mx_strlen(tmp->login) + 2);
		mx_printstr(tmp->group_owner);
		mx_print_tabs(tmp3->l_group_owner - mx_strlen(tmp->group_owner));
		mx_print_tabs(tmp3->l_sym_num - mx_strlen(tmp->sym_num) + 2);
		mx_printstr(tmp->sym_num);
		mx_print_tabs(1);
		mx_printstr(tmp->time_upd);
		mx_print_tabs(tmp3->l_time_upd - mx_strlen(tmp->time_upd) + 1);
		mx_printstr(t2->data);
		mx_printchar('\n');
	}
}
