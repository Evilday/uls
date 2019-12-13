#include "uls.h"

int main(int argc, char *argv[]) {
	t_info *info = mx_info_start(argc - 1, &(argv[1])); // sending without file_name
	
	mx_start(info);
	//system("leaks uls");
	return 0;
}
