#include <ucontext.h>
typedef struct TCB_t{
	TCB_t* next;
	TCB_t* prev;
	ucontext_t context;
	int thread_id;
} TCB_t

void init_TCB(TCB_t* tcb, void* function, void* stackP, int stack_size){
	memset(tcb, '\0', sizeof(TCB_t));
	getcontext(&tcb->context);
	tcb->context.uc_stack.ss_sp = stackP;
	tcb->context.uc_stack.ss_size = (size_t) stack_size;
	makecontext(&tcb->context, function, 0);
}
