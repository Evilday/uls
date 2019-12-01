#include "uls.h"

void mx_advanced_permissions_check(t_info *info) {
	acl_t acl;
	t_info_l *tmp_info_l = info->info_l;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next, tmp_info_l = tmp_info_l->next) {
		acl = acl_get_file(tmp->data, ACL_TYPE_EXTENDED);
		if (acl) {
			mx_strcat(tmp_info_l->access, "+");
			acl_free(acl);
		}
	}
}

void mx_basic_permissions(t_info *info) {
	struct stat fileStat;
	char *str;
	int j = 0;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		stat(tmp->data, &fileStat);
		str = mx_strnew(10);
		str[j++] = S_ISDIR(fileStat.st_mode) ? 'd' : '-';
		str[j++] = fileStat.st_mode & S_IRUSR ? 'r' : '-';
		str[j++] = fileStat.st_mode & S_IWUSR ? 'w' : '-';
		str[j++] = fileStat.st_mode & S_IXUSR ? 'x' : '-';
		str[j++] = fileStat.st_mode & S_IRGRP ? 'r' : '-';
		str[j++] = fileStat.st_mode & S_IWGRP ? 'w' : '-';
		str[j++] = fileStat.st_mode & S_IXGRP ? 'x' : '-';
		str[j++] = fileStat.st_mode & S_IROTH ? 'r' : '-';
		str[j++] = fileStat.st_mode & S_IWOTH ? 'w' : '-';
		str[j++] = fileStat.st_mode & S_IXOTH ? 'x' : '-';
		mx_push_info_l_back(&(info->info_l), str);
		free(str);
		j = 0;
	}
}

void mx_l_flag(t_info *info) {
	mx_basic_permissions(info);
	mx_advanced_permissions_check(info);
}

void mx_take_flags(t_info *info) {
	char *our_flags = mx_strnew(37);

	for (int i = 0; i < info->argc; i++) {
		if (info->where_what[i] == 1) {
			for (int j = 1; info->argv[i][j]; j++)
				if (!mx_strchr(our_flags, info->argv[i][j]))
					our_flags[mx_strlen(our_flags)] = (info->argv[i][j]);
		}
	}
	info->all_our_flags = our_flags;
}

void mx_work_with_flags(t_info *info) {
	for (int i = 0; info->all_our_flags[i]; i++) {
		if (info->all_our_flags[i] == 'l') {
			mx_l_flag(info);
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
