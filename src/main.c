#include "uls.h"

int main(int argc, char *argv[]) {
	t_info *info = mx_info_start(argc - 1, &(argv[1])); // sending without file_name

	mx_start(info);
	// system("leaks uls");
	return 0;
}

// ../../..//
// 7.12s user 3.92s system 42% cpu 25.705 total

// ../../..//Library/Application Support/Slack/Code Cache/js/index-dir:
// total 8
// -rw-------   1 vkmetyk  4242  408 Dec 13 10:55 the-real-index
// drwx------  19 vkmetyk  4242  646 Dec 13 10:54 ..
// drwx------   3 vkmetyk  4242  102 Dec 13 10:55 .