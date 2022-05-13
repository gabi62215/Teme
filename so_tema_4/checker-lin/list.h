#ifndef LIST
#define LIST

#include "list.h"

typedef struct cell {
	void *value;
	struct cell *next;
} cell_t;

cell_t *new_cell(void *value);
void delete_list(cell_t **list, void (*free_value)(void *));

#endif