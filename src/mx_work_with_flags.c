#include "uls.h"

void mx_advanced_permissions_check(t_info *info) {
	acl_t acl;
	t_info_l *tmp_info_l = info->info_l;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next, tmp_info_l = tmp_info_l->next) {
		acl = acl_get_file(tmp->path, ACL_TYPE_EXTENDED);
		if (acl) {
			tmp_info_l->access[10] = '+';
			acl_free(acl);
		}
		if (listxattr(tmp->path, NULL, 0, XATTR_NOFOLLOW))
			tmp_info_l->access[10] = '@';
	}
}

void mx_basic_permissions(t_info *info) {
	struct stat fileStat;
	char *str;
	int j = 0;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		lstat(tmp->path, &fileStat);
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

static char *get_login(uid_t st_uid) {
	struct passwd *pw = getpwuid(st_uid);

	return pw->pw_name;
}

void mx_date_time_for_l(t_info *info) {
	struct stat buff;
	t_uni_list *tmp2 = info->sub_args;
	char *year;
	char buf[100];

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
		lstat(tmp2->path, &buff);
		if (readlink(tmp2->path, buf, 100) > 0) {
			tmp2->data = mx_realloc(tmp2->data
			, mx_strlen(buf) + mx_strlen(tmp2->data) + 4);
			mx_strcat(tmp2->data, " -> ");
			mx_strcat(tmp2->data, buf);
			tmp->access[0] = 'l';
		}
		tmp->time_upd = mx_strndup(((ctime)(&buff.st_mtime) + 4), 12);
		if ((time(0) - buff.st_mtime) > (31536000 / 2)) {
			year = mx_itoa(1970 + (buff.st_mtime / 31536000));
			mx_strcpy(&(tmp->time_upd[8]), year);
			tmp->time_upd[7] = ' ';
			free(year);
		}
		tmp2 = tmp2->next;
	}
}

void mx_group_size_for_l(t_info *info) {
	struct stat buff;
	t_uni_list *tmp2 = info->sub_args;
	struct group *grp;

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next) {
		lstat(tmp2->path, &buff);
		info->total_blocks_l += buff.st_blocks;
		grp = getgrgid(buff.st_gid);
		tmp->nlink = mx_itoa(buff.st_nlink);
		if (grp)
			tmp->group_owner = mx_strdup(grp->gr_name);
		else
			tmp->group_owner = mx_itoa(buff.st_gid);
		if (buff.st_uid)
			tmp->login = get_login(buff.st_uid);
		else
			tmp->login = mx_strdup("root");
		tmp->sym_num = mx_itoa(buff.st_size);
		tmp2 = tmp2->next;
	}
}

// printf("-----------\n");
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
// printf("%ld\t\n", buff.st_ctime);
// printf("-----------\n");
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
			info->flag_l = 1;
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
