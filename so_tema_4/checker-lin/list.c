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
	//printf("nu iteleg\n");
	if (list) {
		//printf("mporti\n");
		cell_t *l = *list;
		//printf("nu iteleg\n");
		while (l) {
			cell_t *aux = l;
			l = l->next;
			//printf("nu iteleg\n");
			free_value(aux->value);
			//printf("nimic\n");
			free(aux);
		}

		*list = NULL;
	}
}