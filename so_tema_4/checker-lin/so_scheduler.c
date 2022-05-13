#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#include "defs.h"
#include "so_scheduler.h"
#include "list.h"
#include "queue.h"

scheduler_t *scheduler;

int get_priority(void *value)
{
	return ((thread_t *)value)->priority;
}

int check_terminated_thread_priority(void *addr)
{
	return 0;
}

void free_thread(void *value)
{
	if (value) {
		thread_t *t = (thread_t *)value;

		pthread_join(t->id, NULL);
		sem_destroy(&t->planned);
		sem_destroy(&t->wait);
		free(t);
	}
	
}

int so_init(unsigned int time_quantum, unsigned int io)
{
	if (scheduler != NULL ||
		io > SO_MAX_NUM_EVENTS || time_quantum <= 0)
		return -1;
	
	int ret;
	scheduler = malloc(sizeof(scheduler_t));
	if (!scheduler)
		return -1;

	scheduler->quantum = time_quantum;
	scheduler->io_devices = io;
	scheduler->thread_no = 0;
	ret = sem_init(&scheduler->finished, 0, 0);
	if (ret < 0)
		return ret;
	
	scheduler->ready = new_queue();
	if (!scheduler->ready) {
		sem_destroy(&scheduler->finished);
		free(scheduler);
		
		return -1;
	}
	
	scheduler->waiting = (queue_t **)calloc(io, sizeof(queue_t *));
	if (!scheduler->waiting) {
		sem_destroy(&scheduler->finished);
		delete_queue(&scheduler->ready, free_thread);
		free(scheduler);

		return -1;
	}

	scheduler->terminated = new_queue();

	for (int i = 0; i < io; i++) {
		scheduler->waiting[i] = new_queue();
		if (!scheduler->waiting[i]) {
			sem_destroy(&scheduler->finished);
			delete_queue(&scheduler->ready, free_thread);
			
			/* free queues up to where you got */
			for (int j = 0; j < i; j++)
				delete_queue(&scheduler->waiting[i], free_thread);

			free(scheduler->waiting);
			free(scheduler);
			return -1;
		}
	}
	
	scheduler->curr_thread = NULL;

	return 0;
}

void *start_thread(void *arg)
{
	thread_t *t = (thread_t *)arg;

	if (!scheduler->curr_thread) {
		scheduler->curr_thread = t;
		t->state = RUNNING;
		sem_post(&scheduler->curr_thread->running);
	} else if (t->priority > scheduler->curr_thread->priority) {
		thread_t *aux = scheduler->curr_thread;
		scheduler->curr_thread = t;
		t->state = RUNNING;
		aux->state = READY;
		insert(scheduler->ready, aux, get_priority);
	} else {
		t->state = READY;
		insert(scheduler->ready, t, get_priority);
	}

	sem_post(&t->planned);

	sem_wait(&t->running);

	t->function(t->priority);

	t->state = TERMINATED;
	insert(scheduler->terminated, t, check_terminated_thread_priority);
	scheduler->curr_thread = pop(scheduler->ready);

	if (scheduler->curr_thread != NULL)
			sem_post(&scheduler->curr_thread->running);

	if (scheduler->curr_thread == NULL && peek(scheduler->ready) == NULL)
			sem_post(&scheduler->finished);

	return NULL;
}

tid_t so_fork(so_handler *func, unsigned int priority)
{
	if (!func || priority > SO_MAX_PRIO)
		return INVALID_TID;

	int ret;

	thread_t *t = malloc(sizeof(thread_t));
	if (!t)
		return -1;

	t->priority = priority;
	t->state = NEW;
	t->function = func;
	t->elapsed_time = 0;
	scheduler->thread_no++;
	ret = sem_init(&t->planned, 0 , 0);
	if (ret < 0) {
		free(t);
		return ret;
	}
	
	ret = sem_init(&t->wait, 0 , 0);
	if (ret < 0) {
		sem_destroy(&t->planned);
		free(t);
	}
	
	ret = sem_init(&t->running, 0 , 0);
	if (ret < 0) {
		sem_destroy(&t->planned);
		sem_destroy(&t->wait);
		free(t);
	}
	
	ret = pthread_create(&t->id, NULL, start_thread, t);
	if (ret < 0) {
		sem_destroy(&t->planned);
		sem_destroy(&t->wait);
		sem_destroy(&t->running);
		free(t);
		return ret;
	}
	
	sem_wait(&t->planned);
	
	if (scheduler->curr_thread != t)
		so_exec();
	
	return t->id;
}

int so_wait(unsigned int io)
{
	if (io >= scheduler->io_devices)
		return -1;

	int ret;
	thread_t *t = scheduler->curr_thread;

	t->state = WAITING;
	ret = insert(scheduler->waiting[io], t, get_priority);
	if (ret < 0)
		return ret;

	scheduler->curr_thread = pop(scheduler->ready);
	if (scheduler->curr_thread)
		sem_post(&scheduler->curr_thread->running);

	sem_wait(&t->running);

	return 0;
}

int so_signal(unsigned int io)
{
	if (io >= scheduler->io_devices)
		return -1;

	int signaled = 0;
	thread_t *p = pop(scheduler->waiting[io]);

	for (; p != NULL; p = pop(scheduler->waiting[io])) {
		p->state = READY;
		insert(scheduler->ready, p, get_priority);
		signaled++;
	}

	// while (p) {
	// 	p->state = READY;
	// 	insert(scheduler->ready, p, get_priority);

	// 	signaled++;
	// 	p = pop(scheduler->waiting[io]);
	// }

	so_exec();
	return signaled;
}

void so_exec(void)
{
	if (!scheduler->curr_thread)
		return;

	scheduler->curr_thread->elapsed_time++;
	int was_switched = 0;

	if (scheduler->curr_thread->elapsed_time == scheduler->quantum) {
		scheduler->curr_thread->state = READY;
		scheduler->curr_thread->elapsed_time = 0;
		insert(scheduler->ready, scheduler->curr_thread, get_priority);

		thread_t *next = pop(scheduler->ready);

		while (next && next->state == TERMINATED) {
			insert(scheduler->terminated, next, check_terminated_thread_priority);
			next = pop(scheduler->ready);
		}

		scheduler->curr_thread = next;
		if (scheduler->curr_thread) {
			scheduler->curr_thread->state = RUNNING;
			sem_post(&scheduler->curr_thread->running);
		}

		was_switched = 1;
	} else if (peek(scheduler->ready) &&
		((thread_t *)peek(scheduler->ready))->priority >
		scheduler->curr_thread->priority) {

		scheduler->curr_thread->state = READY;
		insert(scheduler->ready, scheduler->curr_thread, get_priority);

		thread_t *next = pop(scheduler->ready);

		while (next && next->state == TERMINATED) {
			insert(scheduler->terminated, next, check_terminated_thread_priority);
			next = pop(scheduler->ready);
		}

		scheduler->curr_thread = next;
		if (scheduler->curr_thread) {
			scheduler->curr_thread->state = RUNNING;
			sem_post(&scheduler->curr_thread->running);
		}

		was_switched = 1;
	}

	if (was_switched)
		sem_wait(&scheduler->curr_thread->running);
}

void so_end(void)
{
	if (scheduler) {
		//printf("1end\n");
		if (scheduler->thread_no != 0)
			sem_wait(&scheduler->finished);
		//printf("2\n");
		sem_destroy(&scheduler->finished);
		//printf("3\n");
		delete_queue(&scheduler->ready, free_thread);
		delete_queue(&scheduler->terminated, free_thread);
		//printf("4\n");
		for (int i = 0; i < scheduler->io_devices; i++)
			delete_queue(&scheduler->waiting[i], free);
		//printf("5\n=========\n");
		free(scheduler->waiting);
		free(scheduler);
		scheduler = NULL;
	}
}