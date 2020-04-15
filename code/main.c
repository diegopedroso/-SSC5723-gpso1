#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lista.h"

FILE * logfile;

int randomNumber() {
	return rand() % 100;
}

void * consume(void * arg) {
	while(1) {
		Lista* l = (Lista*) arg;
		//pthread_mutex_lock(getSemaphore(l,FULL));
		sem_wait(getSemaphore(l,FULL));
		pthread_mutex_lock(getSemaphore(l,MUTEX));
		int item = pop(l);
		pthread_mutex_unlock(getSemaphore(l,MUTEX));
		//pthread_mutex_unlock(getSemaphore(l,EMPTY));
		sem_post(getSemaphore(l,EMPTY));
		fprintf(logfile, "Removed %d from buffer\n", item);
		//int value;
		//fprintf(logfile, "nº empty slots: %d\n", sem_getvalue(getSemaphore(l,EMPTY), &value));
	}
}

void * produce(void * arg) {
	while(1) {
		Lista * l = (Lista*) arg;
		int item = randomNumber();
		//pthread_mutex_lock(getSemaphore(l, EMPTY));
		sem_wait(getSemaphore(l,EMPTY));
		pthread_mutex_lock(getSemaphore(l, MUTEX));
		push(l, item);
		pthread_mutex_unlock(getSemaphore(l,MUTEX));
		//pthread_mutex_unlock(getSemaphore(l,FULL));
		sem_post(getSemaphore(l,FULL));
		fprintf(logfile, "Inserted %d in buffer\n", item);
		//int value;
		//fprintf(logfile, "nº full slots: %d\n", sem_getvalue(getSemaphore(l,FULL), &value));
	}
}

// Compile with "gcc main.c lista.c -pthread -o main"
int main(int argc, char *argv[]) {
	// First parameter: Buffer size
	// Second parameter: Number of producer threads
	// Third parameter: Number of consumer threads
	if(argc != 4) {
		fprintf(stderr, "Usage: %s <size_buffer> <n_producers> <n_consumers>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	srand(time(NULL));
	int i;
	logfile = fopen("log.txt", "w");

	int bufferCapacity = atoi(argv[1]);
	Lista *l = initializeLista(bufferCapacity);
	
	int nProducers = atoi(argv[2]);
	int nConsumers = atoi(argv[3]);
	
	pthread_t * producers = malloc(sizeof(pthread_t) * nProducers);
	pthread_t * consumers = malloc(sizeof(pthread_t) * nConsumers);

	for(i = 0; i < nProducers; ++i)
		pthread_create(producers + i, NULL, produce, l);
	for(i = 0; i < nConsumers; ++i)
		pthread_create(consumers + i, NULL, consume, l);
		
	for(i = 0; i < nProducers; ++i)
		pthread_join(producers[i], NULL);
	for(i = 0; i < nConsumers; ++i)
		pthread_join(consumers[i], NULL);

	destroyLista(l);
	fclose(logfile);
	
	return 0;
}
