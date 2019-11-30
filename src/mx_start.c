#include "uls.h"

static bool check_basic_errors(t_info *info) {
	bool flags = 1;
	for (int i = 0; i < info->argc; i++) {
		if (flags) {
			//printf("if\n");
			if (!mx_check_flags(info, i))
				flags = 0;
		}
		else {
			//printf("else\n");
			mx_check_argv(info, i);
		}
	}
	return 1;
}

void mx_start(t_info *info) {
	if (check_basic_errors(info)) {
		// just for look
		for (int i = info->argc - 1; i > 0; i--) {
			if (!info->where_what[i])
				mx_arg_not_exist(info->argv[i]);
		}
		printf("======Info flags and args=======\n");
		printf("INFO = flags = %d , arg = %d\n", info->flags_exist, info->args_exist);
		printf("================================\n");
		// End

		mx_sort_args(info);
		mx_work_with_args(info);
		
		// for (int i = 0; i < info->argc; i++)
		// 	printf("%d", info->where_what[i]);
		// printf("\n");
		
		// printf("all_our_flags = %s\n", info->all_our_flags);

		// struct stat buff;

		// time_t test_time;

		// stat(info->argv[0], &buff);
		// printf("%llu\t", buff.st_ino);
		// printf("%hu\t", buff.st_mode);
		// printf("%hu\t", buff.st_nlink);
		// printf("%u\t", buff.st_uid);
		// printf("%u\t", buff.st_gid);
		// printf("%d\t", buff.st_rdev);
		// printf("%lld\t", buff.st_size);
		// printf("%d\t", buff.st_blksize);
		// printf("%lld\t", buff.st_blocks);
		// printf("%ld\t", buff.st_atime);
		// printf("%ld\t", buff.st_mtime);
		// printf("%ld\t", buff.st_ctime);
		// printf("%s\n", info->argv[0]);

		// test_time = buff.st_mtime;

		printf("===============\n");

		// mx_num_of_cols(info);

		// acl_t acl = NULL;
		// acl = acl_get_file(info->argv[0], ACL_TYPE_ACCESS);
		// ssize_t size = 200;
		// char *str = acl_to_text(acl, NULL);
		// printf("acl_to_text = %s\n", str);

		//DIR *f = opendir(".");
		//struct dirent *d;
		// if (f != 0) {
		//d = readdir(f);
		// 	while ((d = readdir(f)))
		// 		printf("%s\n", d->d_name);
		// }
		// struct stat fileStat;
		//printf("%s", (getgrnam(d->d_name)));

		// for (int i = 0; stat(info->argv[i], &fileStat) >= 0; i++) {
		// 	printf("File Permissions : \t");
		// 	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
		// 	printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
		// 	printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
		// 	printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
		// 	printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
		// 	printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
		// 	printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
		// 	printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
		// 	printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
		// 	printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
		// 	printf("\n");
		// }

		// printf("=====================\n");
		// for (int i = 0; i < info->argc; i++)
		// 	printf("argv[%d] = %s\n", i, info->argv[i]);
		// printf("=====================\n");
	}
}

// dirent
// getpwuid
