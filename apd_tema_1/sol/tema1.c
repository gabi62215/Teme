#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "genetic_algorithm.h"

int main(int argc, char *argv[]) {
	// array with all the objects that can be placed in the sack
	sack_object *objects = NULL;

	// number of objects
	int object_count = 0;

	// maximum weight that can be carried in the sack
	int sack_capacity = 0;

	// number of generations
	int generations_count = 0;

	// number of threads
	int threads = 0;

	// read input
	if (!read_input(&objects, &object_count, &sack_capacity, &generations_count, &threads, argc, argv)) {
		return 0;
	}

	// argument struct to pass to run_genetic_algorithm
	argument *x = malloc(sizeof(argument) * threads);

	// generations used in the algorithm
	individual *current_generation = (individual*) calloc(object_count, sizeof(individual));
	individual *next_generation = (individual*) calloc(object_count, sizeof(individual));

	// initialize parameters for argument
	x->objects = objects;
	x->object_count = object_count;
	x->sack_capacity = sack_capacity;
	x->generations_count = generations_count;
	x->threads = threads;
	x->thread_id = 0;
	x->current_generation = current_generation;
	x->next_generation = next_generation;

	run_genetic_algorithm(x);
	
	//free each atribuite then free argument
	free(objects);
	free(current_generation);
	free(next_generation);

	return 0;
}
