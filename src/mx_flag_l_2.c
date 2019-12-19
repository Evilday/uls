#include "uls.h"

static char *get_login(uid_t st_uid);
static char *time_format(t_info *info, struct stat buff);

void mx_group_size_for_l(t_info *info) {
	struct stat buff;
	t_uni_list *tmp2 = info->sub_args;
	struct group *grp;
	char *theOne;

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
		theOne = mx_strjoin(info->path, tmp2->data);
		lstat(theOne, &buff);
		free(theOne);
		info->total_blocks_l += buff.st_blocks;
		grp = getgrgid(buff.st_gid);
		tmp->nlink = mx_itoa(buff.st_nlink);
		if (grp)
			tmp->group_owner = mx_strdup(grp->gr_name);
		else
			tmp->group_owner = mx_itoa(buff.st_gid);
		tmp->login = get_login(buff.st_uid);
		tmp->sym_num = mx_sym_num(tmp->access[0], buff);
		tmp2 = tmp2->next;
	}
}

void mx_count_tabs_l(t_info *info) {
	t_tabs_l *tabs_l = (t_tabs_l *)malloc(sizeof(t_tabs_l));
	tabs_l->l_nlink = tabs_l->l_login = tabs_l->l_group_owner
		= tabs_l->l_sym_num = tabs_l->l_time_upd = 0;

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
		if (mx_strlen(tmp->nlink) > tabs_l->l_nlink)
			tabs_l->l_nlink = mx_strlen(tmp->nlink);
		if (mx_strlen(tmp->login) > tabs_l->l_login)
			tabs_l->l_login = mx_strlen(tmp->login);
		if (mx_strlen(tmp->group_owner) > tabs_l->l_group_owner)
			tabs_l->l_group_owner = mx_strlen(tmp->group_owner);
		if (mx_strlen(tmp->sym_num) > tabs_l->l_sym_num && mx_strlen(tmp->sym_num) < 9)
			tabs_l->l_sym_num = mx_strlen(tmp->sym_num);
		if (mx_strlen(tmp->time_upd) > tabs_l->l_time_upd)
			tabs_l->l_time_upd = mx_strlen(tmp->time_upd);
	}
	info->tabs_l = tabs_l;
}

void mx_date_time_for_l(t_info *info) {
	struct stat buff;
	t_uni_list *tmp2 = info->sub_args;
	char *theOne;

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
		theOne = mx_strjoin(info->path, tmp2->data);
		lstat(theOne, &buff);
		tmp->time_upd = time_format(info, buff);
		tmp2 = tmp2->next;
		free(theOne);
	}
}

static char *time_format(t_info *info, struct stat buff) {
	char *time_result;
	long time_format;
	char *year;

	if (info->time_flag == 'u')
		time_format = buff.st_atime;
	else if (info->time_flag == 'c')
		time_format = buff.st_ctime;
	else
		time_format = buff.st_mtime;
	if (info->flag_T) {
		time_result = mx_strndup(((ctime)(&time_format) + 4), 20);
	}
	else {
		time_result = mx_strndup(((ctime)(&time_format) + 4), 12);
		if ((time(0) - time_format) > (31536000 / 2)) {
			year = mx_itoa(1970 + (time_format / 31536000));
			mx_strcpy(&(time_result[8]), year);
			time_result[7] = ' ';
			free(year);
		}
	}
	return time_result;
}

static char *get_login(uid_t st_uid) {
	char *user = (char *)malloc(256);
	struct passwd *pw = getpwuid(st_uid);

	if (pw == NULL)
		user = mx_itoa(st_uid);
	else
		mx_strcpy(user, pw->pw_name);
	return user;
}
