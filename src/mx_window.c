#include "uls.h"

static int list_size(t_uni_list *list) {
	int size = 0;

	if (list)
		for (t_uni_list *temp = list; temp; temp = temp->next, size++);

	return size;
}

int mx_num_of_cols(t_info *info) {
	struct winsize w;
	int max_len = 0;
	int cols = 0;
	int lines = 0;

	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next)
		if (max_len < mx_strlen(tmp->data))
			max_len = mx_strlen(tmp->data);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	cols = (w.ws_col / ((8 - (max_len % 8)) + max_len));
	printf("size = %i\n", list_size(info->sub_args));
	lines = list_size(info->sub_args) / cols;
	if (lines == 0 || ((lines % cols) != 0))
		lines++;
	printf("num_of_cols = %i\n", cols);
	printf("lines = %i\n", lines);
	return cols;
}
/*
табуляция ширина нашего окна делится (5) 8 
и остачу прибавить к файлу максимальной длины,
 если остаток 0, то прибавить 8 
*/


/*
(getgrgid(s_info_l->nickname)->gr_name)
*/
