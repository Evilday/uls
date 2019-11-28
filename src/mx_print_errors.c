#include "uls.h"

void mx_invalid_usage() {
    mx_printerr(INVALID_USAGE);
    mx_printerr("\n");
}

void mx_arg_not_exist(char *arg) {
    mx_printerr("uls: ");
    mx_printerr(arg);
    mx_printerr(": No such file or directory");
    mx_printerr("\n");
}
