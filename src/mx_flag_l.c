#include "uls.h"

static void basic_l_permissions(t_info *info, struct stat perm);

void mx_l_permissions(t_info *info) {
	struct stat buff;
	char *arg;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		arg = mx_strjoin(info->path, tmp->data);
		lstat(arg, &buff);
		basic_l_permissions(info, buff);
		free(arg);
	}
	mx_advanced_permissions_check(info);
}

char mx_get_type(struct stat file_stat) {
	char result = '-';

	if ((file_stat.st_mode & S_IFMT) == S_IFCHR)
		return 'c';
	if ((file_stat.st_mode & S_IFMT) == S_IFBLK)
		return 'b';
	if ((file_stat.st_mode & S_IFMT) == S_IFIFO)
		return 'p';
	if ((file_stat.st_mode & S_IFMT) == S_IFSOCK)
		return 's';
	if ((file_stat.st_mode & S_IFMT) == S_IFLNK)
		return 'l';
	if ((file_stat.st_mode & S_IFMT) == S_IFDIR)
		return 'd';
	return result;
}

char mx_get_char(int mode, int is_exec, int is_id) {
	if (mode & is_exec) {
		if (mode & is_id)
			return 's';
		else
			return 'x';
	}
	else {
		if (mode & is_id)
			return 'S';
		else
			return '-';
	}
}

char mx_get_mode(int mode, int user_type) {
	if (user_type == 1)
		return mx_get_char(mode, S_IXUSR, S_ISUID);
	else if (user_type == 2)
		return mx_get_char(mode, S_IXGRP, S_ISGID);
	else {
		if (mode & S_IXOTH) {
			if (mode & S_ISTXT)
				return 't';
			else
				return 'x';
		}
		else {
			if (mode & S_ISTXT)
				return 'T';
			else 
				return '-';
		}
	}
}

static void basic_l_permissions(t_info *info, struct stat perm) {
	char *str;

	str = mx_strnew(10);
	str[0] = mx_get_type(perm);
	str[1] = perm.st_mode & S_IRUSR ? 'r' : '-';
	str[2] = perm.st_mode & S_IWUSR ? 'w' : '-';
	str[3] = mx_get_mode(perm.st_mode, 1);
	str[4] = perm.st_mode & S_IRGRP ? 'r' : '-';
	str[5] = perm.st_mode & S_IWGRP ? 'w' : '-';
	str[6] = mx_get_mode(perm.st_mode, 2);
	str[7] = perm.st_mode & S_IROTH ? 'r' : '-';
	str[8] = perm.st_mode & S_IWOTH ? 'w' : '-';
	str[9] = mx_get_mode(perm.st_mode, 3);
	mx_push_info_l_back(&(info->info_l), str);
	free(str);
}
