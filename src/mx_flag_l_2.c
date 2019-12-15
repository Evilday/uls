#include "uls.h"

static char *get_major (unsigned int rdev);
static char *get_minor (unsigned int rdev);
static char *check_minor(unsigned int rdev);

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

char *mx_sym_num(char access, struct stat buff) {
	char *sym_num = NULL;
	char *major = NULL;
	char *minor = NULL;

	if (access == 'b' || access == 'c') {
		sym_num = get_major(buff.st_rdev);
		major = mx_strjoin(sym_num, ", ");
		free(sym_num);
		minor = get_minor(buff.st_rdev);
		sym_num = mx_strjoin(major, minor);
		free(major);
		free(minor);
	}
	else
		sym_num = mx_itoa(buff.st_size);
	return sym_num;
}

static char *get_major (unsigned int rdev) {
	char *major;

	major = mx_itoa((rdev >> 24) & 0xff);
	while (mx_strlen(major) < 3) {
		char *tmp_str = NULL;

		tmp_str = mx_strjoin(" ", major);
		free(major);
		major = mx_strdup(tmp_str);
		free(tmp_str);
	}
	return major;
}

static char *get_minor (unsigned int rdev) {
	char *minor;

	minor = check_minor(rdev);
	while (mx_strlen(minor) < 3) {
		char *tmp_str = NULL;

		tmp_str = mx_strjoin(" ", minor);
		free(minor);
		minor = mx_strdup(tmp_str);
		free(tmp_str);
	}
	return minor;
}

static char *check_minor(unsigned int rdev) {
	char *minor;

	minor = mx_itoa(rdev & 0xffffff);
	if ((rdev & 0xffffff) > 256) {
		free(minor);
		minor = mx_nbr_to_hex(rdev & 0xffffff);
		while (mx_strlen(minor) < 10) {
			char *tmp_str = mx_strdup(minor);

			free(minor);
			minor = mx_strjoin("0", tmp_str);
			free(tmp_str);
		}
		minor[1] = 'x';
	}
	return minor;
}
