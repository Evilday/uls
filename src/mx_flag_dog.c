#include "uls.h"

static void print_xattr_list(t_info *info, char *key, int vallen) {
	mx_printchar('\n');
	mx_printchar('\t');
	mx_printstr(key);
	mx_printchar('\t');
	mx_print_tabs(info->max_sub_len + 3);
	mx_printint(vallen);
}

static char *get_xattr_string(char *full_path, ssize_t *full_len) {
	char *attributes;

	*full_len = listxattr(full_path, NULL, 0, XATTR_SHOWCOMPRESSION);
	attributes = malloc(*full_len + 1);
	listxattr(full_path, attributes, *full_len, XATTR_SHOWCOMPRESSION);
	attributes[*full_len] = '\0';
	return attributes;
}

void mx_take_xattr_list(t_info *info, char *arg, t_info_l *info_l) {
	char *full_path;
	char *attributes;
	ssize_t full_len;

	if (info_l->access[10] == '@') {
		full_path = mx_strjoin(info->path, arg);
		attributes = get_xattr_string(full_path, &full_len);
		if (full_len > 0) {
			size_t value_len = getxattr(full_path, attributes, NULL,
				0, 0, XATTR_SHOWCOMPRESSION);

			print_xattr_list(info, attributes, value_len);
		}
		free(attributes);
		free(full_path);
	}
}
