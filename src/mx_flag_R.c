#include "uls.h"

static void flag_R_recurtion(t_info *info, char *arg);

void mx_flag_R(t_info *info, char *arg) {
	bool folder_exist = 0;

	
	if (folder_exist) {
		flag_R_recurtion(info, arg);
	}
}

static void flag_R_recurtion(t_info *info, char *arg) {
	if (info && arg) {}
}
