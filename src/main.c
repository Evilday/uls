#include "uls.h"

int main(int argc, char *argv[]) {
	t_info *info = mx_info_start(argc - 1, &(argv[1]));

	mx_start(info);
	for (int i = 0; i < info->argc; i++)
		if (info->where_what[i] == 0)
			return 1;
	return 0;
}
