#include "uls.h"

// for uni_list
t_uni_list *mx_create_uni_list(char *data, char *path, int f) {
	t_uni_list *new_uni_list = (t_uni_list *)malloc(sizeof(t_uni_list));
	char *str;

	if (new_uni_list) {
		new_uni_list->data = mx_strdup(data);
		new_uni_list->next = NULL;
		new_uni_list->folder = f == 4 ?  1 : 0;
		if (path) {
			str = mx_strndup(path, mx_strlen(path) + 1);
			mx_strcat(str, "/");
			new_uni_list->path = mx_strjoin(str, data);
			free(str);
		}
		else
			new_uni_list->path = mx_strdup(data);
	}
	return new_uni_list;
}
void mx_push_uni_list_back(t_uni_list **list, void *data, char *path, int f) {
	t_uni_list *new_uni_list = NULL;
	t_uni_list *temp = *list;

	if (list && (new_uni_list = mx_create_uni_list(data, path, f)) != NULL) {
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
		if (malloc_size(temp->path))
			mx_strdel(&(temp->path));
		*head = temp->next;
		free(temp);
	}
}
