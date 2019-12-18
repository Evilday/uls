#include "uls.h"

t_uni_list *mx_create_uni_list(t_info *info, char *data, int f) {
	t_uni_list *new_uni_list = (t_uni_list *)malloc(sizeof(t_uni_list));

	if (new_uni_list) {
		new_uni_list->data = mx_strdup(data);
		new_uni_list->next = NULL;
		new_uni_list->folder = f == 4 ?  1 : 0;
		new_uni_list->path = info->path;
	}
	return new_uni_list;
}
void mx_push_uni_list_back(t_info *info, t_uni_list **list, void *data, int f) {
	t_uni_list *new_uni_list = NULL;
	t_uni_list *temp = *list;

	if (list && (new_uni_list = mx_create_uni_list(info, data, f)) != NULL) {
		if (*list) {
			while (temp->next)
				temp = temp->next;

			temp->next = new_uni_list;
		}
		else
			*list = new_uni_list;
	}
	if (malloc_size(data))
		free(data);
}

void mx_pop_uni_list_front(t_uni_list **head) {
	t_uni_list *temp = NULL;

	if (head && *head) {
		temp = *head;
		if (malloc_size(temp->data))
			mx_strdel(&(temp->data));
		*head = temp->next;
		free(temp);
	}
}

// void mx_swap_uni_list(t_info *info, int swap) {
// 	int pos = 0;
// 	t_uni_list *prev = NULL;
// 	t_uni_list *curr = info->sub_args;
// 	t_uni_list *temp;

// 	while (pos++ < swap) {
// 		prev = curr;
// 		curr = curr->next;
// 	}
// 	pos = 0;
// 	if (prev)
// 		prev->next = curr->next;
// 	else
// 		info->sub_args = curr->next;
// 	temp = curr->next->next;
// 	curr->next->next = curr;
// 	curr->next = temp;
// }

static void swap_links(t_uni_list *currX, t_uni_list *currY) {
	t_uni_list *temp = currY->next;

	currY->next = currX->next;
	currX->next = temp;
}

void mx_swap_uni_list(t_info *info, int x, int y) {
	int pos = 0;
	t_uni_list *prevX = NULL;
	t_uni_list *currX = info->sub_args;
	t_uni_list *prevY = NULL;
	t_uni_list *currY = info->sub_args;

	while (currX && pos++ != x) {
		prevX = currX;
		currX = currX->next;
	}
	pos = 0;
	while (currY && pos++ != y) { 
		prevY = currY; 
		currY = currY->next; 
	}
	if (prevX)
		prevX->next = currY;
	else
		info->sub_args = currY;
	prevY->next = currX;
	swap_links(currX, currY);
}
