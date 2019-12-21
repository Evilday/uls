#include "uls.h"

static void take_permissions(t_info *info);

void mx_flag_p_or_F(t_info *info, t_uni_list *arg) {
	if (info->p_F_flag == 'F') {
		if (!info->info_l)
			take_permissions(info);
	}
	else if (info->p_F_flag == 'p' && arg->folder)
		write(1, "/", 1);
}

// / - папка
// * - файл може бути виконаний
// | - якщо файл є Fifo
// @ - для якщо це символічне посилання

static void take_permissions(t_info *info) {
	struct stat buff;
	char *arg;
	char *file_type;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		arg = mx_strjoin(info->path, tmp->data);
		lstat(arg, &buff);
		file_type = mx_strnew(1);
		file_type[0] = mx_get_type(buff);
		mx_push_info_l_back(&(info->info_l), file_type);
		free(arg);
	}
}
