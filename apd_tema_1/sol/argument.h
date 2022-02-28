#ifndef ARGUMENT_H
#define ARGUMENT_H
#include "individual.h"
#include "sack_object.h"

// structure for an individual in the genetic algorithm; the chromosomes are an array corresponding to each sack
// object, in order, where 1 means that the object is in the sack, 0 that it is not
typedef struct _argument {
	sack_object *objects;
	int object_count;
	int sack_capacity;
	int generations_count;
	int threads;
	int thread_id;
	individual *current_generation;
	individual *next_generation;
	pthread_barrier_t *barrier;
	pthread_mutex_t *mutex;
} argument;

typedef struct _argument_2 {
	int threads;
	int thread_id;
	individual *arr;
	int object_count;
} argument_2;
#endif