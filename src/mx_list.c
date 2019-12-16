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
