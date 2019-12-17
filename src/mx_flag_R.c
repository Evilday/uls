#include "uls.h"

void mx_flag_R(t_info *info, char *arg) {
	t_uni_list *all_inside = NULL;
	char *path = mx_strjoin(arg, "/");
	char *adventure = NULL;

	mx_push_uni_list_back(info, &(all_inside), ".", 0);
	mx_look_sub_argv(info, arg, all_inside);
	mx_pop_uni_list_front(&(all_inside));
	mx_sort_uni_list(all_inside);
	info->sub_args = all_inside;
	mx_work_with_flags(info);
	mx_print_arg(info, 1);
	if (info->top_flag == 'l')
		for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next)
			mx_pop_info_l_front(&(info->info_l));
	for (t_uni_list *tmp = all_inside; tmp; tmp = tmp->next)
		if (tmp->folder && mx_strcmp(tmp->data, ".") && mx_strcmp(tmp->data, "..")) {
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
	for (t_uni_list *tmp = all_inside; tmp; tmp = tmp->next)
		mx_pop_uni_list_front(&(all_inside));
	free(path);
}
