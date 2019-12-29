#ifndef ULS_H
#define ULS_H

#define INVALID_USAGE "usage: uls [-@ACFGRSTacdfghlmnprtu1] [file ...]"

#include "libmx/inc/libmx.h"

// Uls

#include <errno.h>
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

#define GRN			"\x1B[32m"
#define RED   		"\x1B[31m"
#define YEL   		"\x1B[33m"
#define BLU   		"\x1B[34m"
#define MAG   		"\x1B[35m"
#define RESET 		"\x1B[0m"
#define BLK_F_RED_B "\x1B[0;30;41m"
#define BLK_F_CYAN_B "\x1B[0;30;46m"
#define BLOCK 		"\x1B[0;34;46m"
#define CHR 		"\x1B[0;34;43m"
#define DIR_T 		"\x1B[0;30;42m"
#define DIR_X		"\x1B[0;30;43m"

typedef struct s_tabs_l {
	int l_nlink;
	int l_login;
	int l_group_owner;
	int l_size;
	int l_time_upd;
} t_tabs_l;

typedef struct s_uni_list {
	char *data;
	char *path;
	int folder;
	struct s_uni_list *next;
} t_uni_list;

typedef struct s_info_l {
	char *access;
	char *access_list;
	char *nlink;
	char *login;
	char *group_owner;
	char *size;
	char *time_upd;
	bool minor_major;
	struct s_info_l *next;
} t_info_l;

typedef struct s_info {
	int argc;
	char **argv;
	int num_of_arg;
	bool first_argv;

	bool flags_exist;
	bool file_exist;
	bool folder_exist;

	int *where_what;

	struct s_uni_list *sub_args;
	char *path;

	int num_of_sub;
	int max_sub_len;

	struct s_info_l *info_l;
	struct s_tabs_l *tabs_l;
	int total_blocks_l;

	char print_flag;
	char sort_flag;
	char time_flag;
	char p_F_flag;
	bool flag_a;
	bool flag_A;
	bool flag_R;
	bool flag_G;
	bool flag_h;
	bool flag_dog;
	bool flag_e;
	bool flag_T;
	bool flag_C;
	bool flag_r;
	bool flag_t;
	bool flag_f;
	bool flag_g;
	bool flag_n;
	bool flag_d;
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
void mx_invalid_usage(char sym);
void mx_arg_not_exist(t_info *info);
void mx_is_allowed(char *path);

// mx_print_types
void mx_basic_print(t_info *info);
void mx_print_1(t_info *info);
void mx_print_l(t_info *info);

// mx_print_types_2
void mx_print_semicoma(t_info *info);

// mx_print_types_3
void mx_choose_print_action(t_info *info, t_uni_list *tmp);
void mx_print_l_2(t_info_l *tmp, t_tabs_l *tmp3);

// mx_clear_all
void mx_clear_all(t_info *info);

// mx_work_with_args
void mx_work_with_args(t_info *info);
void mx_work_with_one_arg(t_info *info, char *arg, bool folder);
void mx_default_args(t_info *info);

// mx_work_with_args_2
bool mx_look_sub_argv(t_info *info, char *arg, t_uni_list *save);

// mx_work_with_flags
void mx_work_with_flags(t_info *info);
void mx_l_flag(t_info *info);
void mx_take_flags(t_info *info);

// mx_sort
void mx_sort_args(t_info *info);
void mx_sort_uni_list(t_info *info, t_uni_list *lst);
void mx_sort_with_flags(t_info *info);
void mx_rotate(t_info *info);
void mx_flag_t(t_info *info);

// mx_sort_2
void mx_flag_S(t_info *info);

// mx_window.c
int mx_num_of_cols(t_info *info);

// mx_list
t_uni_list *mx_create_uni_list(t_info *info, char *data, int f);
void mx_push_uni_list_back(t_info *info, t_uni_list **lst, void *data, int f);
void mx_pop_uni_list_front(t_uni_list **head);
void mx_swap_uni_list(t_info *info, int x, int y);

//mx_list_2
t_info_l *mx_create_info_l(char *data);
void mx_push_info_l_back(t_info_l **list, char *data);
void mx_pop_info_l_front(t_info_l **head);
void mx_swap_l(t_info *info, int x, int y);

// mx_flags_a_A
void mx_look_sub_argv_2(t_info *info, DIR *f, t_uni_list *save);

// mx_flag_l
void mx_l_permissions(t_info *info);
char mx_get_type(struct stat file_stat);
char mx_get_char(int mode, int is_exec, int is_id);
char mx_get_mode(int mode, int user_type);

// mx_flag_l_2
void mx_take_group_and_size_for_l(t_info *info);
void mx_count_tabs_l(t_info *info);
void mx_date_time_for_l(t_info *info);

// mx_flag_l_3
char *mx_block_size(t_info_l *info_l, struct stat buff);
void mx_advanced_permissions_check(t_info *info);

// mx_flag_l_4
char *mx_time_format(t_info *info, struct stat buff);

// mx_flag_dog
void mx_take_xattr_list(t_info *info, char *arg, t_info_l *info_l);

// mx_flag_R
void mx_flag_R(t_info *info, char *arg);

// mx_flags_p_F
void mx_flag_p_or_F(t_info *info, t_uni_list *arg);

// mx_flag_h
char *mx_flag_h(char *size);

// mx_flag_G
void mx_print_color(t_info *info, t_uni_list *arg);

// mx_flag_d
void mx_flag_d(t_info *info);

// mx_your_atoi
long long int my_atoi(const char *str);

// mx_on_off_flags
void mx_on_off_flags(t_info *info);

#endif
