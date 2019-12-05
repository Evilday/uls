#include "uls.h"

void mx_l_flag(t_info *info) {
	mx_basic_permissions(info);
	mx_advanced_permissions_check(info);
	mx_group_size_for_l(info);
	mx_date_time_for_l(info);
}

void mx_take_flags(t_info *info) {
	char *our_flags = mx_strnew(37);

	for (int i = 0; i < info->argc; i++) {
		if (info->where_what[i] == 1) {
			for (int j = 1; info->argv[i][j]; j++) {
				for (int p = 0; our_flags[p]; p++)
					if (our_flags[p] == info->argv[i][j])
						our_flags[p] = '0';
						our_flags[mx_strlen(our_flags)] = (info->argv[i][j]);
			}
		}
	}
	for (int i = 0; our_flags[i]; i++) {
		if (our_flags[i] == 'a')
			info->flag_a = 1;
		else if (our_flags[i] == 'A')
			info->flag_A = 1;
	}
	info->all_our_flags = our_flags;
}

void mx_work_with_flags(t_info *info) {
	for (int i = mx_strlen(info->all_our_flags); i >= 0; i--) {
		if (info->all_our_flags[i] == 'l') {
			mx_l_flag(info);
			break;
		}
		else if (info->all_our_flags[i] == '1') {
			//
			break;
		}
	}
}

// stat - Функция stat() вносит в структуру, на которую указывает statbuf,
// информацию, содержащуюся в файле, связанном с указателем filename. Структура stat определена в sys\stat.h.

// -rw-r--r--  1                                   vkmetyk  4242                                   8                               Nov 22 17:13                 		  test.txt
// 			num of hard links to this file               ID of the group owner of the file      num of symbols (bytes) inside   last time modified           file name
// 			buff.st_nlink                                buff.st_gid                            buff.st_size                    buff.st_mtime                readdir(opendir("pos (default ".")"))

// коли в аргументи потрапляє перший агрумент, що не є флагом, то більше флаги не потрібно відшукувати

// char *time_info = mx_strndup(((ctime)(&buff.st_mtime) + 4), 12);
// 	printf("Time:%s\n", time_info);
// 	free(time_info);

// struct stat fileStat;

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

// -l src main.c Makefile --- ..

// 1 2 2 2 0 2
