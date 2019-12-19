#include "uls.h"

static void basic_tab_print(t_info *info, int arg_len);
static void print_name(char *str, char *data);

void mx_basic_print(t_info *info) {
	int j;
	int sub_r;
	int num_of_lines = mx_num_of_cols(info);

	for (int i = 0; i < num_of_lines; i++) {
		j = 0;
		sub_r = 0;
		for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next, j++) {
			if ((j + num_of_lines - i) % num_of_lines == 0) {
				mx_printstr(tmp->data);
				if (sub_r + num_of_lines < info->num_of_sub) {
					basic_tab_print(info, mx_strlen(tmp->data));
				}
			}
			++sub_r;
		}
		mx_printchar('\n');
	}
}

void mx_print_1(t_info *info) {
	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		mx_printstr(tmp->data);
		mx_printchar('\n');
	}
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
		mx_print_tabs(mx_strlen(tmp->sym_num) < 9 ? tmp3->l_sym_num
			- mx_strlen(tmp->sym_num) + 2 : 2); // не вірно рахує таби в папці /usr/bin/
		mx_printstr(tmp->sym_num);
		mx_print_tabs(1);
		mx_printstr(tmp->time_upd);
		mx_print_tabs(tmp3->l_time_upd - mx_strlen(tmp->time_upd) + 1);
		print_name(info->path, t2->data);
		mx_printchar('\n');
	}
}

static void basic_tab_print(t_info *info, int arg_len) {
	int max_tabs = info->max_sub_len / 8 + 1;
	int tab_len = arg_len / 8;

	if (tab_len < max_tabs) {
		write(1, "\t", 1);
		tab_len++;
	}
	while (max_tabs > tab_len) {
		write(1, "\t", 1);
		tab_len++;
	}
}

static void print_name(char *str, char *data) {
	char *buf = mx_strnew(256);
	char *theOne;

	theOne = mx_strjoin(str, data);
	if (readlink(theOne, buf, 256) > 0) {
		mx_printstr(data);
		mx_printstr(" -> ");
		mx_printstr(buf);
	}
	else
		mx_printstr(data);
	free(theOne);
	free(buf);
}
