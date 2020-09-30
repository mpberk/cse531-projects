#include "q.h"

extern qElement** ReadyQ;
extern qElement Curr_Thread;

void start_thread(void (*function)(void)){
	void* stack = malloc(8192);
	TCB_t* temp_tcb = (TCB_t*) malloc(sizeof(TCB_t));
	init_TCB(temp_tcb, function, stack, 8192);
}

void run(){
	Curr_Thread = DelQueue(ReadyQ);
	ucontext-t parent;
	getcontext(&parent);
	swapcontext(&parent, &(Curr_Thread->context));
}
void yield(){
	TCB_t Prev_Thread;
	AddQueue(Ready_Q, Curr_Thread);
	Prev_Thread = Curr_Thread;
	Curr_Thread = DelQueue(ReadyQ);
	swapcontext(&(Prev_Thread->context),&(Curr_Thread->context)); 
}
void printID(TCB_t tcb){
	printf("%d", tcb->thread_id);
}
