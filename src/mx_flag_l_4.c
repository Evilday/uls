#include "uls.h"

static long detect_time_type(t_info *info, struct stat buff) {
	long time_format;

	if (info->time_flag == 'u')
		time_format = buff.st_atime;
	else if (info->time_flag == 'c')
		time_format = buff.st_ctime;
	else
		time_format = buff.st_mtime;
	return time_format;
}

char *mx_time_format(t_info *info, struct stat buff) {
	char *time_result;
	long time_format = detect_time_type(info, buff);

	if (info->flag_T)
		time_result = mx_strndup(((ctime)(&time_format) + 4), 20);
	else {
		if ((time(0) - time_format) > (31536000 / 2)) {
			char *time_check = mx_strndup(((ctime)(&time_format) + 4), 20);

			time_result = mx_strnew(12);
			mx_strncpy(time_result, time_check, 7);
			mx_strcat(time_result, time_check + 15);
			free(time_check);
		}
		else
			time_result = mx_strndup(((ctime)(&time_format) + 4), 12);
	}
	return time_result;
}
