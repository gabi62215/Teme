#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#include "defs.h"
#include "so_scheduler.h"
#include "list.h"
#include "queue.h"

scheduler_t *scheduler;

/* get thread priority */
int get_priority(void *value)
{
	return ((thread_t *)value)->priority;
}

/* used in order to use queue as list */
int no_priority(void *addr)
{
	return 0;
}

/* free thread structure */
void free_thread(void *value)
{
	if (value) {
		thread_t *t = (thread_t *)value;

		pthread_join(t->id, NULL);
		sem_destroy(&t->planned);
		sem_destroy(&t->running);
		free(t);
	}
}

/* initialize scheduler structure */
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

	ret = pthread_mutex_init(&scheduler->lock, NULL);
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

/*
 * plan thread, wait for the thread to be running in order
 * to execute function. After the thread finished its work
 * add it to terminated queue to be freed later and get the
 * next ready thread
 */
void *start_thread(void *arg)
{
	thread_t *t = (thread_t *)arg;

	pthread_mutex_lock(&scheduler->lock);
	if (!scheduler->curr_thread) {
		scheduler->curr_thread = t;
		sem_post(&scheduler->curr_thread->running);
	} else if (t->priority > scheduler->curr_thread->priority) {
		insert(scheduler->ready, scheduler->curr_thread, get_priority);
		scheduler->curr_thread = t;
		sem_post(&scheduler->curr_thread->running);
	} else
		insert(scheduler->ready, t, get_priority);

	pthread_mutex_unlock(&scheduler->lock);
	sem_post(&t->planned);

	sem_wait(&t->running);

	t->function(t->priority);

	pthread_mutex_lock(&scheduler->lock);
	insert(scheduler->terminated, t, no_priority);
	scheduler->curr_thread = pop(scheduler->ready);

	if (scheduler->curr_thread)
		sem_post(&scheduler->curr_thread->running);

	if (!scheduler->curr_thread && !peek(scheduler->ready))
		sem_post(&scheduler->finished);

	pthread_mutex_unlock(&scheduler->lock);
	return NULL;
}

/* create new thread and pass it the start_thread function */
tid_t so_fork(so_handler *func, unsigned int priority)
{
	if (!func || priority > SO_MAX_PRIO)
		return INVALID_TID;

	int ret;

	thread_t *t = malloc(sizeof(thread_t));

	if (!t)
		return -1;

	t->priority = priority;
	t->function = func;
	t->elapsed_time = 0;
	scheduler->thread_no++;
	ret = sem_init(&t->planned, 0, 0);
	if (ret < 0) {
		free(t);
		return ret;
	}

	ret = sem_init(&t->running, 0, 0);
	if (ret < 0) {
		sem_destroy(&t->planned);
		free(t);
	}

	ret = pthread_create(&t->id, NULL, start_thread, t);
	if (ret < 0) {
		sem_destroy(&t->planned);
		sem_destroy(&t->running);
		free(t);
		return ret;
	}

	sem_wait(&t->planned);

	return t->id;
}

/*
 * wait for io device, by adding thread to its specific
 * io queue. Also pop the next ready thread
 */
int so_wait(unsigned int io)
{
	if (io >= scheduler->io_devices)
		return -1;

	int ret;

	pthread_mutex_lock(&scheduler->lock);
	thread_t *t = scheduler->curr_thread;

	ret = insert(scheduler->waiting[io], t, get_priority);
	if (ret < 0)
		return ret;

	scheduler->curr_thread = pop(scheduler->ready);
	if (scheduler->curr_thread)
		sem_post(&scheduler->curr_thread->running);
	pthread_mutex_unlock(&scheduler->lock);
	sem_wait(&t->running);

	return 0;
}

/* Signal all threads waiting for io that they are ready for execution */
int so_signal(unsigned int io)
{
	if (io >= scheduler->io_devices)
		return -1;

	int signaled = 0;

	pthread_mutex_lock(&scheduler->lock);
	thread_t *p = pop(scheduler->waiting[io]);

	for (; p != NULL; p = pop(scheduler->waiting[io])) {
		insert(scheduler->ready, p, get_priority);
		signaled++;
	}
	pthread_mutex_unlock(&scheduler->lock);

	return signaled;
}

/*
 * Increment time elapsed
 * If time expires switch to next ready thread
 * If the current thread has a lower priority thread also switch
 */
void so_exec(void)
{
	pthread_mutex_lock(&scheduler->lock);
	if (!scheduler->curr_thread)
		return;

	scheduler->curr_thread->elapsed_time++;
	int was_switched = 0;

	if (scheduler->curr_thread->elapsed_time == scheduler->quantum) {
		scheduler->curr_thread->elapsed_time = 0;
		insert(scheduler->ready, scheduler->curr_thread, get_priority);

		scheduler->curr_thread = pop(scheduler->ready);

		if (scheduler->curr_thread)
			sem_post(&scheduler->curr_thread->running);

		was_switched = 1;
	} else if (peek(scheduler->ready) &&
		((thread_t *)peek(scheduler->ready))->priority >
		scheduler->curr_thread->priority) {

		insert(scheduler->ready, scheduler->curr_thread, get_priority);

		scheduler->curr_thread = pop(scheduler->ready);

		if (scheduler->curr_thread)
			sem_post(&scheduler->curr_thread->running);

		was_switched = 1;
	}
	pthread_mutex_unlock(&scheduler->lock);
	if (was_switched)
		sem_wait(&scheduler->curr_thread->running);
}

/* Free scheduler strucuture */
void so_end(void)
{
	if (scheduler) {
		if (scheduler->thread_no != 0)
			sem_wait(&scheduler->finished);

		for (int i = 0; i < scheduler->io_devices; i++)
			delete_queue(&scheduler->waiting[i], free_thread);
		free(scheduler->waiting);

		sem_destroy(&scheduler->finished);
		pthread_mutex_destroy(&scheduler->lock);
		delete_queue(&scheduler->ready, free_thread);
		delete_queue(&scheduler->terminated, free_thread);

		free(scheduler);
		scheduler = NULL;
	}
}
