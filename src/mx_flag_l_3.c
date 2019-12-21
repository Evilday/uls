#include "uls.h"

static char *get_major (unsigned int rdev);
static char *get_minor (unsigned int rdev);
static char *check_minor(unsigned int rdev);

void mx_advanced_permissions_check(t_info *info) {
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

char *mx_block_size(t_info_l *info_l, struct stat buff) {
	char *size = NULL;
	char *major = NULL;
	char *minor = NULL;

	if (info_l->access[0] == 'b' || info_l->access[0] == 'c') {
		size = get_major(buff.st_rdev);
		major = mx_strjoin(size, ", ");
		free(size);
		minor = get_minor(buff.st_rdev);
		if (mx_strlen(minor) > 3)
			info_l->minor_major = 1;
		size = mx_strjoin(major, minor);
		free(major);
		free(minor);
	}
	else
		size = mx_itoa(buff.st_size);
	return size;
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
