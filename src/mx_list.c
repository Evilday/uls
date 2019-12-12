#include "uls.h"

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

// for flag l

t_info_l *mx_create_info_l(char *data) {
	t_info_l *new_info_l = (t_info_l *)malloc(sizeof(t_info_l));

	if (new_info_l) {
		new_info_l->access = mx_strnew(mx_strlen(data) + 2);
		mx_strcpy(new_info_l->access, data);
		if (!((new_info_l->access)[10]))
		 	(new_info_l->access)[10] = ' ';
		 	(new_info_l->access)[11] = ' ';
		new_info_l->nlink = NULL;
		new_info_l->login = NULL;
		new_info_l->group_owner = NULL;
		new_info_l->sym_num = NULL;
		new_info_l->time_upd = NULL;
		new_info_l->next = NULL;
	}
	return new_info_l;
}
void mx_push_info_l_back(t_info_l **list, char *data) {
	t_info_l *new_info_l = NULL;
	t_info_l *temp = *list;

	if (list && (new_info_l = mx_create_info_l(data)) != NULL) {
		if (*list) {
			while (temp->next)
				temp = temp->next;

			temp->next = new_info_l;
		}
		else
			*list = new_info_l;
	}
}

void mx_pop_info_l_front(t_info_l **head) {
	t_info_l *temp = NULL;

	if (head && *head) {
		temp = *head;
		mx_strdel(&(temp->access));
		mx_strdel(&(temp->nlink));
		if (malloc_size(temp->login))
			mx_strdel(&(temp->login));
		mx_strdel(&(temp->group_owner));
		mx_strdel(&(temp->sym_num));
		mx_strdel(&(temp->time_upd));
		*head = temp->next;
		free(temp);
	}
}
