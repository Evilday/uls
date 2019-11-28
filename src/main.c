#include "uls.h"

static t_info *info_start(int argc, char **argv) {
	t_info *info = (t_info *)malloc(sizeof(t_info));

	info->argc = argc;
	info->argv = argv;
	info->flags_exist = 0;
	info->args_exist = 0;
	info->flags = NULL;
	info->exist = (bool *)malloc(sizeof(bool) * argc);

	for (int i = 0; i < argc; i++)
		info->exist[i] = 1;

	return info;
}

int main(int argc, char *argv[]) {
	t_info *info = info_start(argc - 1, &(argv[1])); // sending without file_name
	printf("===========What inside==========\n");
	for (int i = 0; i < info->argc; i++)
		printf("i = %d - %s\n", info->exist[i], info->argv[i]);
	printf("================================\n");
	mx_start(info);
	//system("leaks uls");
	return 0;
}
