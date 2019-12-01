#include "uls.h"

static t_info *info_start(int argc, char **argv) {
	t_info *info = (t_info *)malloc(sizeof(t_info));

	info->argc = argc;
	info->argv = argv;
	info->flags_exist = 0;
	info->args_exist = 0;
	info->where_what = (int *)malloc(sizeof(int) * argc);
	info->all_our_flags = NULL;
	info->sub_args = NULL;
	info->info_l = NULL;
	info->flag_a = 0;
	info->flag_A = 0;
	info->flag_l = 0;

	for (int i = 0; i < argc; i++)
		info->where_what[i] = 0;

	return info;
}

int main(int argc, char *argv[]) {
	t_info *info = info_start(argc - 1, &(argv[1])); // sending without file_name
	printf("===========What inside==========\n");
	for (int i = 0; i < info->argc; i++)
		printf("%s\n", info->argv[i]);
	printf("================================\n");
	mx_start(info);
	//system("leaks uls");
	return 0;
}
