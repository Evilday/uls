#ifndef ULS_H
#define ULS_H

#define INVALID_USAGE "usage: uls [-l] [file ...]"

#include "libmx/inc/libmx.h"

// Uls

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

#include <wchar.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/acl.h>
#include <sys/xattr.h>

typedef struct s_info {
	int argc;
	char **argv;

	bool flags_exist;
	bool args_exist;

	char *flags;
	bool *exist;
} t_info;

// mx_check_errors
bool mx_check_flags(t_info *info, int i);
bool mx_check_argv(t_info *info, int i);

// mx_start
void mx_start(t_info *info);

// mx_del_all
void mx_del_info(t_info **info);

// print_errors
void mx_invalid_usage();
void mx_arg_not_exist(char *arg);

// mx_work_with_args
void mx_work_with_args(t_info *info);
void mx_sort_args(t_info *info);

// mx_work_with_flags
void mx_work_with_flags(t_info *info);

#endif
