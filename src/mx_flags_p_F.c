#include "uls.h"

static void check_flag_G(t_info *info, t_uni_list *arg);

void mx_flag_p_or_F(t_info *info, t_uni_list *arg) {
	check_flag_G(info, arg);
	if (info->p_F_flag == 'F') {
		struct stat buff;
		char *full_path = mx_strjoin(info->path, arg->data);

		lstat(full_path, &buff);
		free(full_path);
		if ((buff.st_mode & S_IFMT) == S_IFLNK)
			write (1, "@", 1);
		else if ((buff.st_mode & S_IFMT) == S_IFDIR)
			write(1, "/", 1);
		else if (buff.st_mode & S_IXUSR)
			write(1, "*", 1);
		else if (buff.st_mode & S_IFIFO)
			write(1, "|", 1);
	}
	else if (info->p_F_flag == 'p' && arg->folder)
		write(1, "/", 1);
}

static void check_flag_G(t_info *info, t_uni_list *arg) {
	if (info->flag_G)
		mx_print_color(info, arg);
	else
		mx_printstr(arg->data);
}

// / - папка
// * - файл може бути виконаний
// | - якщо файл є Fifo
// @ - для якщо це символічне посилання
