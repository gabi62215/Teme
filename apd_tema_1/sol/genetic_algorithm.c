#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "genetic_algorithm.h"

int read_input(sack_object **objects, int *object_count, int *sack_capacity, int *generations_count,int *threads, int argc, char *argv[])
{
	FILE *fp;

	if (argc < 4) {
		fprintf(stderr, "Usage:\n\t./tema1 in_file generations_count thread_number\n");
		return 0;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		return 0;
	}

	if (fscanf(fp, "%d %d", object_count, sack_capacity) < 2) {
		fclose(fp);
		return 0;
	}

	if (*object_count % 10) {
		fclose(fp);
		return 0;
	}

	sack_object *tmp_objects = (sack_object *) calloc(*object_count, sizeof(sack_object));

	for (int i = 0; i < *object_count; ++i) {
		if (fscanf(fp, "%d %d", &tmp_objects[i].profit, &tmp_objects[i].weight) < 2) {
			free(objects);
			fclose(fp);
			return 0;
		}
	}

	fclose(fp);

	*generations_count = (int) strtol(argv[2], NULL, 10);

	*threads = (int) strtol(argv[3], NULL, 10);
	
	if (*generations_count == 0) {
		free(tmp_objects);

		return 0;
	}

	*objects = tmp_objects;

	return 1;
}

void print_objects(const sack_object *objects, int object_count)
{
	for (int i = 0; i < object_count; ++i) {
		printf("%d %d\n", objects[i].weight, objects[i].profit);
	}
}

void print_generation(const individual *generation, int limit)
{
	for (int i = 0; i < limit; ++i) {
		for (int j = 0; j < generation[i].chromosome_length; ++j) {
			printf("%d ", generation[i].chromosomes[j]);
		}

		printf("\n%d - %d\n", i, generation[i].fitness);
	}
}

void print_best_fitness(const individual *generation)
{
	printf("%d\n", generation[0].fitness);
}

void compute_fitness_function(const sack_object *objects, individual *generation, int object_count, int sack_capacity)
{
	int weight;
	int profit;

	for (int i = 0; i < object_count; ++i) {
		weight = 0;
		profit = 0;

		for (int j = 0; j < generation[i].chromosome_length; ++j) {
			if (generation[i].chromosomes[j]) {
				weight += objects[j].weight;
				profit += objects[j].profit;
			}
		}

		generation[i].fitness = (weight <= sack_capacity) ? profit : 0;
	}
}

int cmpfunc(const void *a, const void *b)
{
	int i;
	individual *first = (individual *) a;
	individual *second = (individual *) b;

	int res = second->fitness - first->fitness; // decreasing by fitness
	if (res == 0) {
		int first_count = 0, second_count = 0;

		for (i = 0; i < first->chromosome_length && i < second->chromosome_length; ++i) {
			first_count += first->chromosomes[i];
			second_count += second->chromosomes[i];
		}

		res = first_count - second_count; // increasing by number of objects in the sack
		if (res == 0) {
			return second->index - first->index;
		}
	}

	return res;
}

void merge(individual *arr, int left, int middle, int right) {
    int i = 0;
    int j = 0;
    int k = 0;
    int left_length = middle - left + 1;
    int right_length = right - middle;
    individual *left_array = (individual*) calloc(left_length, sizeof(individual));
    individual *right_array = (individual*) calloc(right_length, sizeof(individual));
   
    // copy values to left array 
    for (int i = 0; i < left_length; i ++) {
        memcpy(&left_array[i],&arr[left + i],sizeof(individual));
    }
  
    // copy values to right array 
    for (int j = 0; j < right_length; j ++) {
        memcpy(&right_array[j],&arr[middle + 1 + j],sizeof(individual));
    }
   
    i = 0;
    j = 0;
    // chose from right and left arrays and copy */
    while (i < left_length && j < right_length) {
        if (cmpfunc(&left_array[i],&right_array[j]) <= 0) { 
            memcpy(&arr[left + k],&left_array[i],sizeof(individual));
            i ++;
        } else {
            memcpy(&arr[left + k],&right_array[j],sizeof(individual));
            j ++;
        }
        k ++;
    }
    // copy the remaining values to the array 
    while (i < left_length) {
        memcpy(&arr[left + k],&left_array[i],sizeof(individual));
        k ++;
        i ++;
    }
    while (j < right_length) {
        memcpy(&arr[left + k],&right_array[j],sizeof(individual));
        k ++;
        j ++;
    }


    // free arrays
    free(right_array);
    free(left_array);
}

void print_gen_fit(individual *generation,int n)
{
	printf("| ");
	for(int i = 0; i < n; i++)
		printf("%d ",generation[i].fitness);

	printf("|\n");
}

/* 
   merges all parts that the threads
   had sorted to finally sort the array 
*/

void merge_sections(individual *arr,int threads,int aggregation, 
	int numbers_per_thread, int length) {
	for(int i = 0; i < threads; i = i + 2) {
        int left = i * (numbers_per_thread * aggregation);
        int right = ((i + 2) * numbers_per_thread * aggregation) - 1;
        int middle = left + (numbers_per_thread * aggregation) - 1;

        if (right >= length) {
            right = length - 1;
        }
        
        merge(arr, left, middle, right);
    }
    if (threads / 2 >= 1) {
        merge_sections(arr, threads / 2, aggregation * 2, numbers_per_thread, length);
    }
}

void merge_sort(individual *arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

/* 
   function that is passed to each thread,
   it computes bounds for each thread and
   performs usual merge sort  
*/
void *thread_merge_sort(void *arg)
{
	argument_2 *x = (argument_2 *)arg;
	int numbers_per_thread = x->object_count / x->threads;
	int offset = x->object_count % x->threads;
    int left = x->thread_id * (numbers_per_thread);
    int right = (x->thread_id + 1) * (numbers_per_thread) - 1; 

    if (x->thread_id == x->threads - 1) {
        right += offset;
    }
    
    if (left < right) {
        merge_sort(x->arr, left, right);
    }

    return NULL;
}

/*
   creates the threads and feeds them
   the thread_merge_sort function,also
   it calls merge_sections have the threads
   have finished
*/
void actual_sort(individual *arr,int len,int num_threads)
{
	pthread_t threads[num_threads];
	argument_2 *arg = malloc(sizeof(argument_2) * num_threads);

	for (int i = 0; i < num_threads; i++) {
		arg[i].threads = num_threads;
		arg[i].thread_id = i;
		arg[i].arr = arr;
		arg[i].object_count = len;
    	int rc = pthread_create(&threads[i], NULL, thread_merge_sort, (void *)&arg[i]);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for(long i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

	int numbers_per_thread = len / num_threads;

	merge_sections(arr, num_threads, 1,numbers_per_thread,len);

    free(arg);

}

void mutate_bit_string_1(const individual *ind, int generation_index)
{
	int i, mutation_size;
	int step = 1 + generation_index % (ind->chromosome_length - 2);

	if (ind->index % 2 == 0) {
		// for even-indexed individuals, mutate the first 40% chromosomes by a given step
		mutation_size = ind->chromosome_length * 4 / 10;
		for (i = 0; i < mutation_size; i += step) {
			ind->chromosomes[i] = 1 - ind->chromosomes[i];
		}
	} else {
		// for even-indexed individuals, mutate the last 80% chromosomes by a given step
		mutation_size = ind->chromosome_length * 8 / 10;
		for (i = ind->chromosome_length - mutation_size; i < ind->chromosome_length; i += step) {
			ind->chromosomes[i] = 1 - ind->chromosomes[i];
		}
	}
}

void mutate_bit_string_2(const individual *ind, int generation_index)
{
	int step = 1 + generation_index % (ind->chromosome_length - 2);

	// mutate all chromosomes by a given step
	for (int i = 0; i < ind->chromosome_length; i += step) {
		ind->chromosomes[i] = 1 - ind->chromosomes[i];
	}
}

void crossover(individual *parent1, individual *child1, int generation_index)
{
	individual *parent2 = parent1 + 1;
	individual *child2 = child1 + 1;
	int count = 1 + generation_index % parent1->chromosome_length;

	memcpy(child1->chromosomes, parent1->chromosomes, count * sizeof(int));
	memcpy(child1->chromosomes + count, parent2->chromosomes + count, (parent1->chromosome_length - count) * sizeof(int));

	memcpy(child2->chromosomes, parent2->chromosomes, count * sizeof(int));
	memcpy(child2->chromosomes + count, parent1->chromosomes + count, (parent1->chromosome_length - count) * sizeof(int));
}

void copy_individual(const individual *from, const individual *to)
{
	memcpy(to->chromosomes, from->chromosomes, from->chromosome_length * sizeof(int));
}

void free_generation(individual *generation)
{
	int i;

	for (i = 0; i < generation->chromosome_length; ++i) {
		free(generation[i].chromosomes);
		generation[i].chromosomes = NULL;
		generation[i].fitness = 0;
	}
}

void *run_genetic_algorithm(void *arg)
{
	argument *x = (argument *)arg;
	int count, cursor;
	individual *tmp = NULL;

	// set initial generation (composed of object_count individuals with a single item in the sack)
	for (int i = 0; i < x->object_count; ++i) {
		x->current_generation[i].fitness = 0;
		x->current_generation[i].chromosomes = (int*) calloc(x->object_count, sizeof(int));
		x->current_generation[i].chromosomes[i] = 1;
		x->current_generation[i].index = i;
		x->current_generation[i].chromosome_length = x->object_count;

		x->next_generation[i].fitness = 0;
		x->next_generation[i].chromosomes = (int*) calloc(x->object_count, sizeof(int));
		x->next_generation[i].index = i;
		x->next_generation[i].chromosome_length = x->object_count;
	}

	// iterate for each generation
	for (int k = 0; k < x->generations_count; ++k) {
		cursor = 0;
	
		// compute fitness and sort by it
		compute_fitness_function(x->objects, x->current_generation, x->object_count, x->sack_capacity);
		actual_sort(x->current_generation,x->object_count,x->threads);
		
		// keep first 30% children (elite children selection)
		count = x->object_count * 3 / 10;
		for (int i = 0; i < count; ++i) {
			copy_individual(x->current_generation + i, x->next_generation + i);
		}
		cursor = count;
		

		// mutate first 20% children with the first version of bit string mutation
		count = x->object_count * 2 / 10;
		for (int i = 0; i < count; ++i) {
			copy_individual(x->current_generation + i, x->next_generation + cursor + i);
			mutate_bit_string_1(x->next_generation + cursor + i, k);
		}
		cursor += count;

		// mutate next 20% children with the second version of bit string mutation
		count = x->object_count * 2 / 10;
		for (int i = 0; i < count; ++i) {
			copy_individual(x->current_generation + i + count, x->next_generation + cursor + i);
			mutate_bit_string_2(x->next_generation + cursor + i, k);
		}
		cursor += count;

		// crossover first 30% parents with one-point crossover
		// (if there is an odd number of parents, the last one is kept as such)
		count = x->object_count * 3 / 10;
		if (count % 2 == 1) {
			copy_individual(x->current_generation + x->object_count - 1, x->next_generation + cursor + count - 1);
			count--;
		}
		
		for (int i = 0; i < count; i += 2) {
			crossover(x->current_generation + i, x->next_generation + cursor + i, k);
		}
		
		// switch to new generation
		tmp = x->current_generation;
		x->current_generation = x->next_generation;
		x->next_generation = tmp;
			
		for (int i = 0; i < x->object_count; ++i) {
			x->current_generation[i].index = i;
		}

		if (k % 5 == 0) {
			print_best_fitness(x->current_generation);
		}
	}
	
	compute_fitness_function(x->objects, x->current_generation, x->object_count, x->sack_capacity);
	actual_sort(x->current_generation,x->object_count,x->threads);
	print_best_fitness(x->current_generation);
	
	return NULL;
}