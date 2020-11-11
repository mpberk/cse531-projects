#ifndef SEM_H
#define SEM_H

#include "threads.h"
typedef struct Semaphore_t{
	int counter;
	TCB_t** Queue;
} Semaphore_t;

Semaphore_t* CreateSem(int InputValue){
	Semaphore_t* newSem = (Semaphore_t*) malloc(sizeof(Semaphore_t));
	newSem->counter = InputValue;
	newSem->Queue = newQueue();
	return newSem;
}

void P(Semaphore_t* sem){
	sem->counter--;
	if(sem->counter < 0){
		TCB_t* storeThread = DelQueue(ReadyQ);
		AddQueue(sem->Queue, storeThread);
		swapcontext(&(storeThread->context), &((*ReadyQ)->context));
	}

}

void V(Semaphore_t* sem){	
	sem->counter++;
	if(sem->counter < 0){
		TCB_t* runThread = DelQueue(sem->Queue);
		AddQueue(ReadyQ, runThread);
	}	
	yield();
}

#endif
