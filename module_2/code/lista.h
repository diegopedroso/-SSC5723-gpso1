#ifndef _LISTA_H_
#define _LISTA_H_

#define MUTEX 0
#define FULL 1
#define EMPTY 2

typedef struct lista_s Lista;

Lista* initializeLista(int capacity);
int pop(Lista * l);
void push(Lista * l, int item);
void destroyLista(Lista* l);
void* getSemaphore(Lista* l, int type);

#endif
