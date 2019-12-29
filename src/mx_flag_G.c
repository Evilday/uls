#include "uls.h"

static void print_dir(char *res);
static void print_reg_file(char *res);
static char *get_type_res(struct stat buff, char *res);
static char *permissions(struct stat buff);

void mx_print_color(t_info *info, t_uni_list *arg) {
    struct stat buff;
    char *f_path = mx_strjoin(info->path, arg->data);
    char *res;

    lstat(f_path, &buff);
    res = permissions(buff);
    free(f_path);
    (S_ISDIR(buff.st_mode)) ?  print_dir(res) :
    (S_ISLNK(buff.st_mode)) ?  mx_printstr(MAG) :
    (S_ISBLK(buff.st_mode)) ?  mx_printstr(BLOCK) :
    (S_ISCHR(buff.st_mode)) ?  mx_printstr(CHR) :
    (S_ISFIFO(buff.st_mode)) ?  mx_printstr(YEL) :
    (S_ISSOCK(buff.st_mode)) ?  mx_printstr(GRN) :
    (S_ISREG(buff.st_mode)) ?  print_reg_file(res) :
        mx_printstr(arg->data);
    mx_printstr(arg->data);
    mx_printstr(RESET);
    free(res);
}

static void print_dir(char *res) {
    if (res[8] == 'w' && (res[9] == 't' || res[9] == 'T'))
        mx_printstr(DIR_T);
    else if (res[8] == 'w' && res[9] == 'x')
        mx_printstr(DIR_X);
    else
        mx_printstr(BLU);   
}

static void print_reg_file(char *res) {
    if (res[3] == 's' || res[3] == 'S')
        mx_printstr(BLK_F_RED_B );
    else if (res[6] == 's' || res[6] == 'S')
        mx_printstr(BLK_F_CYAN_B);
    else if (res[3] == 'x')
        mx_printstr(RED);
    else
        mx_printstr(RESET);
}

static char *permissions(struct stat buff) {
    char *res = mx_strnew(10);

    get_type_res(buff, res);
    res[1] = (S_IRUSR & buff.st_mode) ? 'r' : '-';
    res[2] = (S_IWUSR & buff.st_mode) ? 'w' : '-';
    res[3] = (buff.st_mode & S_IXUSR) ?
            ((buff.st_mode & S_ISUID) ? 's' : 'x') :
            ((buff.st_mode & S_ISUID) ? 'S' : '-');
    res[4] = (S_IRGRP & buff.st_mode) ? 'r' : '-';
    res[5] = (S_IWGRP & buff.st_mode) ? 'w' : '-';
    res[6] = (buff.st_mode & S_IXGRP) ?
            ((buff.st_mode & S_ISGID) ? 's' : 'x') :
            ((buff.st_mode & S_ISGID) ? 'S' : '-');
    res[7] = (S_IROTH & buff.st_mode) ? 'r' : '-';
    res[8] = (S_IWOTH & buff.st_mode) ? 'w' : '-';
    res[9] = (buff.st_mode & S_IXOTH) ?
            ((buff.st_mode & S_ISTXT) ? 't' : 'x') :
            ((buff.st_mode & S_ISTXT) ? 'T' : '-');
    return res;
}

static char *get_type_res(struct stat buff, char *res) {
    res[0] = (buff.st_mode & S_IFMT) == S_IFBLK ? 'b' :
             (buff.st_mode & S_IFMT) == S_IFCHR ? 'c' :
             (buff.st_mode & S_IFMT) == S_IFDIR ? 'd' :
             (buff.st_mode & S_IFMT) == S_IFSOCK ? 's' :
             (buff.st_mode & S_IFMT) == S_IFIFO ? 'p' :
             (buff.st_mode & S_IFMT) == S_IFLNK ? 'l' : '-';
    return res;
}
