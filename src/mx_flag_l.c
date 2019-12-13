#include "uls.h"

static char *get_login(uid_t st_uid);

void mx_advanced_permissions_check(t_info *info) {
	acl_t acl;
	t_info_l *tmp_info_l = info->info_l;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next, tmp_info_l = tmp_info_l->next) {
		acl = acl_get_file(tmp->path, ACL_TYPE_EXTENDED);
		if (acl) {
			tmp_info_l->access[10] = '+';
			acl_free(acl);
		}
		if (listxattr(tmp->path, NULL, 0, XATTR_NOFOLLOW))
			tmp_info_l->access[10] = '@';
	}
}

void mx_basic_permissions(t_info *info) {
	struct stat fileStat;
	char *str;
	int j = 0;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		lstat(tmp->path, &fileStat);
		str = mx_strnew(10);
		str[j++] = S_ISDIR(fileStat.st_mode) ? 'd' : '-';
		str[j++] = fileStat.st_mode & S_IRUSR ? 'r' : '-';
		str[j++] = fileStat.st_mode & S_IWUSR ? 'w' : '-';
		str[j++] = fileStat.st_mode & S_IXUSR ? 'x' : '-';
		str[j++] = fileStat.st_mode & S_IRGRP ? 'r' : '-';
		str[j++] = fileStat.st_mode & S_IWGRP ? 'w' : '-';
		str[j++] = fileStat.st_mode & S_IXGRP ? 'x' : '-';
		str[j++] = fileStat.st_mode & S_IROTH ? 'r' : '-';
		str[j++] = fileStat.st_mode & S_IWOTH ? 'w' : '-';
		str[j++] = fileStat.st_mode & S_IXOTH ? 'x' : '-';
		mx_push_info_l_back(&(info->info_l), str);
		free(str);
		j = 0;
	}
}

void mx_date_time_for_l(t_info *info) {
	struct stat buff;
	t_uni_list *tmp2 = info->sub_args;
	char *year;
	char *buf = mx_strnew(260);

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
		lstat(tmp2->path, &buff);
		if (readlink(tmp2->path, buf, 255) > 0) {
			tmp2->data = mx_realloc(tmp2->data
			, mx_strlen(buf) + mx_strlen(tmp2->data) + 4);
			mx_strcat(tmp2->data, " -> ");
			mx_strcat(tmp2->data, buf);
			tmp->access[0] = 'l';
		}
		tmp->time_upd = mx_strndup(((ctime)(&buff.st_mtime) + 4), 12);
		if ((time(0) - buff.st_mtime) > (31536000 / 2)) {
			year = mx_itoa(1970 + (buff.st_mtime / 31536000));
			mx_strcpy(&(tmp->time_upd[8]), year);
			tmp->time_upd[7] = ' ';
			free(year);
		}
		tmp2 = tmp2->next;
	}
	free(buf);
}

void mx_group_size_for_l(t_info *info) {
	struct stat buff;
	t_uni_list *tmp2 = info->sub_args;
	struct group *grp;

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
		lstat(tmp2->path, &buff);
		info->total_blocks_l += buff.st_blocks;
		grp = getgrgid(buff.st_gid);
		tmp->nlink = mx_itoa(buff.st_nlink);
		if (grp)
			tmp->group_owner = mx_strdup(grp->gr_name);
		else
			tmp->group_owner = mx_itoa(buff.st_gid);
		if (buff.st_uid)
			tmp->login = get_login(buff.st_uid);
		else
			tmp->login = mx_strdup("root");
		tmp->sym_num = mx_itoa(buff.st_size);
		tmp2 = tmp2->next;
	}
}

static char *get_login(uid_t st_uid) {
	struct passwd *pw = getpwuid(st_uid);

	return pw->pw_name;
}
