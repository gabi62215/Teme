#include "queue.h"
#include "so_scheduler.h"

#define NEW 0
#define READY 1
#define RUNNING 2
#define WAITING 3
#define TERMINATED 4

typedef struct {
	tid_t id;
	int state;
	unsigned int priority;
	int elapsed_time;
	so_handler *function;

	sem_t planned;
	sem_t wait;
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
} scheduler_t;