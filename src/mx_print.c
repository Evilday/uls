#include "uls.h"

static void basic_print(t_info *info, int num_of_lines);
static void print_1(t_info *info);
static void print_l(t_info *info);

void mx_print_tabs(int n) {
	for (int i = 0; i < n; i++)
		write(1, " ", 1);
}

void mx_print_arg(t_info *info, bool folder) {
	if (folder) {
		if (info->first_argv)
			info->first_argv = 0;
		else
			mx_printchar('\n');
		if (info->num_of_arg > 1) {
			char *str = mx_up_to_one(info->sub_args->path);

			mx_printstr(str);
			free(str);
			mx_printstr(":\n");
		}
		else
			info->num_of_arg = 0;
	}
	else
		info->first_argv = 0;

	if (info->flags_exist) {
		if (info->top_flag == '0' || info->top_flag == 'S') {
			int num_of_lines = mx_num_of_cols(info);

			basic_print(info, num_of_lines);
		}
		else if (info->top_flag == 'l') {
			mx_count_tabs_l(info);
			if (folder) {
				mx_printstr("total ");
				mx_printint(info->total_blocks_l);
				mx_printchar('\n');
			}
			print_l(info);
			info->total_blocks_l = 0;
		}
		else if (info->top_flag == '1') {
			print_1(info);
		}
	}
	else {
		int num_of_lines = mx_num_of_cols(info);

		basic_print(info, num_of_lines);
	}
}

static void basic_print(t_info *info, int num_of_lines) {
	int j;
	int sub_r;
	int tab_len = 0;

	for (int i = 0; i < num_of_lines; i++) {
		j = 0;
		sub_r = 0;
		for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next, j++) {
			if ((j + num_of_lines - i) % num_of_lines == 0) {
				mx_printstr(tmp->data);
				if (sub_r + num_of_lines < info->num_of_sub) {
					tab_len = info->max_sub_len - mx_strlen(tmp->data);
					mx_print_tabs(tab_len + (8 - (info->max_sub_len % 8)));
				}
			}
			++sub_r;
		}
		mx_printchar('\n');
	}
}

static void print_1(t_info *info) {
	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		mx_printstr(tmp->data);
		mx_printchar('\n');
	}
}

static void print_l(t_info *info) {
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
		mx_print_tabs(mx_strlen(tmp->sym_num) < 9 ? tmp3->l_sym_num
			- mx_strlen(tmp->sym_num) + 2 : 2);
		mx_printstr(tmp->sym_num);
		mx_print_tabs(1);
		mx_printstr(tmp->time_upd);
		mx_print_tabs(tmp3->l_time_upd - mx_strlen(tmp->time_upd) + 1);
		mx_printstr(t2->data);
		mx_printchar('\n');
	}
}
