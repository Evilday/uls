#include "uls.h"

static void swap_links(t_info_l *currX, t_info_l *currY);

t_info_l *mx_create_info_l(char *data) {
	t_info_l *new_info_l = (t_info_l *)malloc(sizeof(t_info_l));

	if (new_info_l) {
		new_info_l->access = mx_strnew(12);
		mx_strcpy(new_info_l->access, data);
	 	(new_info_l->access)[10] = ' ';
	 	(new_info_l->access)[11] = ' ';
	 	new_info_l->access_list = NULL;
		new_info_l->nlink = NULL;
		new_info_l->login = NULL;
		new_info_l->group_owner = NULL;
		new_info_l->size = NULL;
		new_info_l->time_upd = NULL;
		new_info_l->next = NULL;
		new_info_l->minor_major = 0;
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
		if (malloc_size(temp->access_list))
			mx_strdel(&(temp->access_list));
		mx_strdel(&(temp->group_owner));
		mx_strdel(&(temp->size));
		mx_strdel(&(temp->time_upd));
		*head = temp->next;
		free(temp);
	}
}

void mx_swap_l(t_info *info, int x, int y) {
	int pos = 0;
	t_info_l *prevX = NULL;
	t_info_l *currX = info->info_l;
	t_info_l *prevY = NULL;
	t_info_l *currY = info->info_l;

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
		info->info_l = currY;
	prevY->next = currX;
	swap_links(currX, currY);
}

static void swap_links(t_info_l *currX, t_info_l *currY) {
	t_info_l *temp = currY->next;

	currY->next = currX->next;
	currX->next = temp;
}
