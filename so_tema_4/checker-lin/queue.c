#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void *peek(queue_t *q)
{
	if (!q->front)
		return NULL;
	
	return q->front->value;
}

void *pop(queue_t *q)
{
	if (!q->front)
		return NULL;

	cell_t *aux = q->front;
	void *value = q->front->value;
	q->front = aux->next;

	free(aux);

	return value;
}

queue_t *new_queue(void)
{
	queue_t *q = malloc(sizeof(queue_t));
	if (q) {
		q->front = NULL;
		q->back = NULL;
	}

	return q;
}

void delete_queue(queue_t **q, void (*free_value)(void *))
{
	//printf("ce naiba\n");
	delete_list(&((*q)->front), free_value);
	//printf("aici\n");
	free(*q);
	*q = NULL;
}

int insert(queue_t *q, void *value, int (*get_priority)(void *))
{
	int value_priority = get_priority(value);

	cell_t *to_insert = new_cell(value);
	if (!to_insert)
		return -1;

	if (!q->front) {
		q->front = to_insert;
		q->back = to_insert;
	} else if (get_priority(q->front->value) < value_priority) {
		to_insert->next = q->front;
		q->front = to_insert;
	} else {
		cell_t *p = q->front;
		cell_t *ant = NULL;

		while (p != NULL && get_priority(q->front->value) > value_priority) {
			ant = p;
			p = p->next;
		}

		if (!p) {
			ant->next = to_insert;
			q->back = to_insert;
		} else {
			to_insert->next = p->next;
			p->next = to_insert;
		}
	}

	return 0;
}