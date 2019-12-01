#include "uls.h"

void mx_invalid_usage() {
	mx_printerr(INVALID_USAGE);
	mx_printerr("\n");
}

void mx_arg_not_exist(t_info *info) {
	for (int i = 0; i < info->argc; i++)
		if (!info->where_what[i]) {
			mx_printerr("uls: ");
			mx_printerr(info->argv[i]);
			mx_printerr(": No such file or directory");
			mx_printerr("\n");
		}
}

void mx_print_arg(t_info *info) {
	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		mx_printstr(tmp->data);
		mx_printchar('\n');
	}
	mx_printchar('\n');
	if (info->flag_l) {
		t_uni_list *tmp2 = info->sub_args;
		for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
			printf("%s ", tmp->access);
			printf("%d ", tmp->nlink);
			printf("%s ", tmp->login);
			printf("%d ", tmp->group_owner);
			printf("%d ", tmp->sym_num);
			printf("%s ", tmp->time_upd);
			printf("%s ", tmp2->data);
			printf("\n");
			tmp2 = tmp2->next;
		}
	}
	printf("\n");
}
