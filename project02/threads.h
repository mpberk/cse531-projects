#ifndef THREADS_H
#define THREADS_H

#include "q.h"
#include "TCB.h"

// Global queue of TCBs
q_element *ReadyQ;

// Global pointer to thread under execution
q_element *Curr_Thread;

// Global thread id count
int id_count = 0;

// Get ID of thread
int get_id (q_element *thread)
{
  return ((TCB_t*)(thread->payload))->thread_id;
  //               thread                        : pointer to q_element
  //               thread->payload               : void pointer to tcb
  //      (TCB_t*)(thread->payload)              : TCB_t pointer to tcb
  //     ((TCB_t*)(thread->payload))->thread_id  : id
};

// Get pointer to context from thread
ucontext_t *get_context_ptr(q_element *item)
{
  return &(((TCB_t*)(item->payload))->context);
  //                 item                       : pointer to q_element
  //                 item->payload              : void pointer to tcb
  //        (TCB_t*)(item->payload)             : TCB_t pointer to tcb
  //       ((TCB_t*)(item->payload))->context   : context that exists in TCB
  //     &(((TCB_t*)(item->payload))->context)  : pointer to context
};

void start_thread(void *function, void *args)
{
  // allocate a stack (via malloc) of a certain size (choose 8192)
  int stack_size = 8192;
  void *stack = malloc(stack_size);
  
  // allocate a TCB (via malloc)
  TCB_t *tcb = (TCB_t*) malloc(sizeof(TCB_t));
  q_element *thread = NewItem();
  thread->payload = (void*) tcb;
  
  // call init_TCB with appropriate arguments
  init_TCB(tcb, function, args, stack, stack_size);
  
  // Add a thread_id (use a counter)
  tcb->thread_id = id_count;
  id_count++;
  
  // call addQ to add this TCB into the "ReadyQ" which is a global head pointer  
  AddQueue(&ReadyQ, thread);
};

void run()
{
  Curr_Thread = DelQueue(&ReadyQ);
  ucontext_t parent; // get a place to store the main context, for faking
  getcontext(&parent); // magic sauce
  swapcontext(&parent, get_context_ptr(Curr_Thread)); // start the first round
};

void yield() // similar to run
{
  q_element *Prev_Thread;
  AddQueue(&ReadyQ, Curr_Thread);
  Prev_Thread = Curr_Thread;
  Curr_Thread = DelQueue(&ReadyQ);
  // swap the context, from Prev_Thread to the thread pointed to Curr_Thread
  swapcontext(get_context_ptr(Prev_Thread), get_context_ptr(Curr_Thread));
};

#endif
