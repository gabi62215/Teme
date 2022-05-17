#include "queue.h"
#include "so_scheduler.h"

typedef struct {
	tid_t id;
	unsigned int priority;
	int elapsed_time;
	so_handler *function;

	sem_t planned;
	sem_t running;
} thread_t;

typedef struct {
	unsigned int quantum;
	unsigned int io_devices;
	thread_t *curr_thread;
	int thread_no;

	queue_t *ready;
	queue_t *terminated;
	queue_t **waiting;

	sem_t finished;
	pthread_mutex_t lock;
} scheduler_t;
