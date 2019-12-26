#include "uls.h"

static void flag_R_check_folder(t_info *info, char *arg, t_uni_list *check);

void mx_flag_R(t_info *info, char *arg) {
	t_uni_list *all_inside = NULL;
	mx_push_uni_list_back(info, &(all_inside), ".", 0);
	mx_look_sub_argv(info, arg, all_inside);
	mx_pop_uni_list_front(&(all_inside));
	mx_sort_uni_list(info, all_inside);
	info->sub_args = all_inside;
	mx_work_with_flags(info);
	mx_print_arg(info, 1);
	all_inside = info->sub_args;
	mx_clear_all(info);
	flag_R_check_folder(info, arg, all_inside);
	while (all_inside)
		mx_pop_uni_list_front(&(all_inside));
}

static void flag_R_check_folder(t_info *info, char *arg, t_uni_list *check) {
	char *path = mx_strjoin(arg, "/");
	char *adventure = NULL;

	for (t_uni_list *tmp = check; tmp; tmp = tmp->next)
		if (tmp->folder && mx_strcmp(tmp->data, ".")
			&& mx_strcmp(tmp->data, "..")) {
			DIR *f;

			adventure = mx_strjoin(path, tmp->data);
			if ((f = opendir(adventure))) {
				closedir(f);
				mx_flag_R(info, adventure);
			}
			else
				mx_is_allowed(adventure);
			free(adventure);
		}
	free(path);
}
