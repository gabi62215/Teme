#ifndef QUEUE
#define QUEUE

#include "list.h"

typedef struct queue {
	cell_t *front, *back;
} queue_t;

void *peek(queue_t *q);
void *pop(queue_t *q);
queue_t *new_queue(void);
void delete_queue(queue_t **q, void (*free_value)(void *));
int insert(queue_t *q, void *value, int (*get_priority)(void *));

#endif