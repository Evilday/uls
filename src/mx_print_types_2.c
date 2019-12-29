#include "uls.h"

static int plus_words_len_iteration(t_info *info, t_uni_list *arg);

void mx_print_semicoma(t_info *info) {
	struct winsize w;
	int words_len = 0;
	int temp = 0;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		temp = words_len;
		words_len += plus_words_len_iteration(info, tmp);
		if (tmp->next)
			words_len += 2;
		if (words_len >= w.ws_col && (words_len -= temp))
			write(1, "\n", 1);
		mx_choose_print_action(info, tmp);
		if (tmp->next)
			write(1, ", ", 2);
	}
	write(1, "\n", 1);
}

static int plus_words_len_iteration(t_info *info, t_uni_list *arg) {
	int plus_len = mx_strlen(arg->data);
	
	if (info->p_F_flag != '0') {
		struct stat buff;
		char *full_path = mx_strjoin(info->path, arg->data);

		lstat(full_path, &buff);
		free(full_path);
		if ((buff.st_mode & S_IFMT) == S_IFLNK 
			|| ((buff.st_mode & S_IFMT) == S_IFDIR) 
			|| (buff.st_mode & S_IXUSR) 
			|| (buff.st_mode & S_IFIFO))
			plus_len++;
	}
	return plus_len;
}
