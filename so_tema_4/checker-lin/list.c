#include <stdlib.h>
#include <stdio.h>
#include "list.h"

cell_t *new_cell(void *value)
{
	cell_t *cell = malloc(sizeof(cell_t));

	if (cell) {
		cell->value = value;
		cell->next = NULL;
	}

	return cell;
}

void delete_list(cell_t **list, void (*free_value)(void *))
{
	if (list) {
		cell_t *l = *list;

		while (l) {
			cell_t *aux = l;

			l = l->next;
			free_value(aux->value);
			free(aux);
		}

		*list = NULL;
	}
}
