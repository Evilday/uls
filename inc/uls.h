#ifndef ULS_H
#define ULS_H

#define INVALID_USAGE "usage: uls [-l] [file ...]"

#include "libmx/inc/libmx.h"

// Uls

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <wchar.h>
#include <pwd.h>
#include <grp.h>

typedef struct s_tabs_l {
	int l_nlink;
	int l_login;
	int l_group_owner;
	int l_sym_num;
	int l_time_upd;
} t_tabs_l;

typedef struct s_uni_list {
	char *data;
	char *path;
	int folder;
	struct s_uni_list *next;
} t_uni_list;

typedef struct s_info_l {
	char *access; // доступ до файлів
	char *nlink;
	char *login;
	char *group_owner;
	char *sym_num;
	char *time_upd;
	struct s_info_l *next;
} t_info_l;

typedef struct s_info {
	int argc;
	char **argv;
	int num_of_arg; // кількість аргументів для виводу
	bool first_argv; // щоб перевірити, чи ми виводимо перший аргумент

	bool flags_exist; // чи є якісь флаги серез аргументів,  що поступили
	bool file_exist; // чи є файл серез аргументів, що поступили
	bool folder_exist; // чи є папка серез аргументів, що поступили

	int *where_what; // 0 - не валідна, 1 - флажок, 2 - файл, 3 - папка, 4 - ігнор

	// char *all_our_flags; // список всіх наших флагів, які нам прийшли

	struct s_uni_list *sub_args; // назви файлів, які є в аргументі
	int num_of_sub; // кількість елементів в агрументі
	int max_sub_len; // найдовше слово серед елементів аргумента

	struct s_info_l *info_l; // всі данні для роботи з l флагом
	struct s_tabs_l *tabs_l; // кількість пробілів для кожного елементу флага l при виводі
	int total_blocks_l;

	char top_flag; // type for print (l, 1, S)
	bool flag_a;
	bool flag_A;
	bool flag_R;
	bool flag_G;
	bool flag_h;
	bool flag_dog; // flag @
	bool flag_e;
	bool flag_T;
	bool flag_C;
	bool flag_r;
	bool flag_t;
	bool flag_u;
	bool flag_c;
} t_info;

// mx_check_errors
char *mx_up_to_one(char *str);
bool mx_check_flags(t_info *info, int i);
bool mx_check_argv(t_info *info, int i);

// mx_start
void mx_start(t_info *info);

// mx_info_prepare
t_info *mx_info_start(int argc, char **argv);

// mx_print
void mx_print_tabs(int n);
void mx_print_arg(t_info *info, bool folder);

// mx_print_errors
void mx_invalid_usage();
void mx_arg_not_exist(t_info *info);

// mx_work_with_args
void mx_work_with_args(t_info *info);
void mx_work_with_one_arg(t_info *info, char *arg, bool folder);

// mx_work_with_args_2
bool mx_look_sub_argv(t_info *info, char *arg);

// mx_work_with_flags
void mx_work_with_flags(t_info *info);
void mx_l_flag(t_info *info);
void mx_take_flags(t_info *info);

// mx_sort
void mx_sort_args(t_info *info);
void mx_sort_uni_list(t_uni_list *lst);

// mx_window.c
int mx_num_of_cols(t_info *info);

// mx_list
t_uni_list *mx_create_uni_list(char *data, char *path, int folder);
void mx_push_uni_list_back(t_uni_list **list, void *data, char *path, int f);
void mx_pop_uni_list_front(t_uni_list **head);
t_info_l *mx_create_info_l(char *data);
void mx_push_info_l_back(t_info_l **list, char *data);
void mx_pop_info_l_front(t_info_l **head);

// mx_flags_a_A
void mx_look_sub_argv_2(t_info *info, char *arg, DIR *f, struct dirent *d);

// mx_flag_l
void mx_l_permissions(t_info *info);
void mx_basic_l_permissions(t_info *info, unsigned long perm);
void mx_advanced_permissions_check(t_info *info);
void mx_date_time_for_l(t_info *info);
void mx_group_size_for_l(t_info *info);

// mx_flag_l_2
void mx_count_tabs_l(t_info *info);
char *mx_sym_num(char access, struct stat buff);

// mx_flag_R
void mx_flag_R(t_info *info, char *arg);

#endif
