#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include "lista.h"

struct lista_s {
	int * buffer;
	int beg, end, capacity;
	pthread_mutex_t mutex;
	sem_t full, empty;
};

void* getSemaphore(Lista* l, int type) {
	switch(type) {
		case MUTEX:
			return &l->mutex;
		case FULL:
			return &l->full;
		case EMPTY:
			return &l->empty;
	}
	return NULL;
}

Lista* initializeLista(int capacity) {
	Lista* l = (Lista*) malloc(sizeof(Lista));
	l->buffer = (int*) malloc(sizeof(int) * capacity);
	l->beg = l->end = 0;
	l->capacity = capacity;
	pthread_mutex_init(&l->mutex, NULL);
	//pthread_mutex_init(&l->full, NULL);
	//pthread_mutex_init(&l->empty, NULL);
	sem_init(&l->full, 0, 1);
	sem_init(&l->empty, 0, capacity);
	//pthread_mutex_lock(&l->full);
	sem_wait(&l->full);
	return l;
}

int pop(Lista * l) {
	int item = l->buffer[l->beg];
	l->beg = (l->beg + 1) % l->capacity;
	return item;
}

void push(Lista * l, int item) {
	l->buffer[l->end] = item;
	l->end = (l->end + 1) % l->capacity;
}

void destroyLista(Lista* l) {
	pthread_mutex_destroy(&l->mutex);
	//pthread_mutex_destroy(&l->full);
	//pthread_mutex_destroy(&l->empty);
	sem_destroy(&l->full);
	sem_destroy(&l->empty);
	free(l->buffer);
	free(l);
}
