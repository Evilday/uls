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
	for (t_uni_list *tmp = all_inside; tmp; tmp = tmp->next)
		mx_pop_uni_list_front(&(all_inside));
}

// static void is_link(t_info *info, char *full_name) {
// 	char *buf = mx_strnew(256);

// 	theOne = mx_strjoin(str, data);
// 	if (readlink(full_name, buf, 256) > 0) {
// 		if ((f = opendir(buf))) {
// 			closedir(f);
// 			mx_flag_R(info, buf);
// 		}
// 	}
// 	free(buf);
// }

static void flag_R_check_folder(t_info *info, char *arg, t_uni_list *check) {
	char *path = mx_strjoin(arg, "/");
	char *adventure = NULL;

	for (t_uni_list *tmp = check; tmp; tmp = tmp->next)
		adventure = mx_strjoin(path, tmp->data);
		if (tmp->folder && mx_strcmp(tmp->data, ".") 
			&& mx_strcmp(tmp->data, "..")) {
			DIR *f;

			if ((f = opendir(adventure))) {
				closedir(f);
				mx_flag_R(info, adventure);
			}
			else
				mx_is_allowed(adventure);
		}
		// else
		// 	is_link(info, adventure);
		free(adventure);
	free(path);
}
