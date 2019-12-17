#include "uls.h"

static char *get_login(uid_t st_uid);
static void basic_l_permissions(t_info *info, unsigned long perm);
static void advanced_permissions_check(t_info *info);

void mx_l_permissions(t_info *info) {
	struct stat buff;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		char *arg = mx_strjoin(info->path, tmp->data);

		lstat(arg, &buff);
		basic_l_permissions(info, buff.st_mode);
		free(arg);
	}
	advanced_permissions_check(info);
}

void mx_date_time_for_l(t_info *info) {
	struct stat buff;
	t_uni_list *tmp2 = info->sub_args;
	char *year;
	char *buf = mx_strnew(260);

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
		char *theOne = mx_strjoin(info->path, tmp2->data);

		lstat(theOne, &buff);
		if (readlink(theOne, buf, 255) > 0) {
			tmp2->data = mx_realloc(tmp2->data
			, mx_strlen(buf) + mx_strlen(tmp2->data) + 4);
			mx_strcat(tmp2->data, " -> ");
			mx_strcat(tmp2->data, buf);
		}
		tmp->time_upd = mx_strndup(((ctime)(&buff.st_mtime) + 4), 12);
		if ((time(0) - buff.st_mtime) > (31536000 / 2)) {
			year = mx_itoa(1970 + (buff.st_mtime / 31536000));
			mx_strcpy(&(tmp->time_upd[8]), year);
			tmp->time_upd[7] = ' ';
			free(year);
		}
		tmp2 = tmp2->next;
		free(theOne);
	}
	free(buf);
}

void mx_group_size_for_l(t_info *info) {
	struct stat buff;
	t_uni_list *tmp2 = info->sub_args;
	struct group *grp;

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
		char *theOne = mx_strjoin(info->path, tmp2->data);

		lstat(theOne, &buff);
		free(theOne);
		info->total_blocks_l += buff.st_blocks;
		grp = getgrgid(buff.st_gid);
		tmp->nlink = mx_itoa(buff.st_nlink);
		if (grp)
			tmp->group_owner = mx_strdup(grp->gr_name);
		else
			tmp->group_owner = mx_itoa(buff.st_gid);
		if (buff.st_uid) {
			tmp->login = get_login(buff.st_uid); ///////////////
		}
		else
			tmp->login = mx_strdup("root");
		tmp->sym_num = mx_sym_num(tmp->access[0], buff);
		tmp2 = tmp2->next;
	}
}

static char *get_login(uid_t st_uid) {
	struct passwd *pw = getpwuid(st_uid);

	return pw->pw_name;
}

static void basic_l_permissions(t_info *info, unsigned long perm) {
	char *str;

	str = mx_strnew(10);
	str[0] = S_ISDIR(perm) ? 'd' : '-';
	str[0] = S_ISLNK(perm) ? 'l' : str[0];
	str[0] = S_ISCHR(perm) ? 'c' : str[0];
	str[0] = S_ISBLK(perm) ? 'b' : str[0];
	str[1] = perm & S_IRUSR ? 'r' : '-';
	str[2] = perm & S_IWUSR ? 'w' : '-';
	str[3] = perm & S_IXUSR ? 'x' : '-';
	str[4] = perm & S_IRGRP ? 'r' : '-';
	str[5] = perm & S_IWGRP ? 'w' : '-';
	str[6] = perm & S_IXGRP ? 'x' : '-';
	str[7] = perm & S_IROTH ? 'r' : '-';
	str[8] = perm & S_IWOTH ? 'w' : '-';
	str[9] = perm & S_IXOTH ? 'x' : '-';
	mx_push_info_l_back(&(info->info_l), str);
	free(str);
}

static void advanced_permissions_check(t_info *info) {
	acl_t acl;
	t_info_l *tmp_info_l = info->info_l;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next
		, tmp_info_l = tmp_info_l->next) {
		char *arg = mx_strjoin(info->path, tmp->data);

		acl = acl_get_file(arg, ACL_TYPE_EXTENDED);
		if (listxattr(arg, NULL, 0, XATTR_NOFOLLOW) > 0)
				tmp_info_l->access[10] = '@';
		else if (acl) {
			tmp_info_l->access[10] = '+';
			acl_free(acl);
		}
		free(arg);
	}
}
