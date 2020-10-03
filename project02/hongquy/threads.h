#ifndef THREADS_H
#define THREADS_H

#include "q.h"


extern TCB_t** ReadyQ;

extern TCB_t* Curr_Thread;
int counter = 0;

void start_thread(void (*function)(void)){
	
	void* stack = malloc(8192);

	TCB_t* temp_tcb = NewItem();
	
	init_TCB(temp_tcb, function, stack, 8192);
	
	temp_tcb->thread_id = counter;
        counter++;
	
	AddQueue(ReadyQ, temp_tcb);	
}

void run(){

	Curr_Thread = DelQueue(ReadyQ);
//	printf("Remove a function from the queue and put it into Curr_Thread\n");

	ucontext_t parent;
	getcontext(&parent);
//	printf("Parent context acquired\n");

	swapcontext(&parent, &(Curr_Thread->context));

}
void printID(TCB_t* tcb){
	printf(" thread ID:%d\n", tcb->thread_id);
}
void yield(){
	TCB_t* Prev_Thread;
	AddQueue(ReadyQ, Curr_Thread);
	Prev_Thread = Curr_Thread;
	Curr_Thread = DelQueue(ReadyQ);
//	printID(Curr_Thread);
	swapcontext(&(Prev_Thread->context),&(Curr_Thread->context)); 
}

#endif
