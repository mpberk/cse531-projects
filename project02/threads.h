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

void start_thread(void (*function)(void))
{
  // allocate a stack (via malloc) of a certain size (choose 8192)
  int stack_size = 8192;
  void *stack = malloc(stack_size);
  
  // allocate a TCB (via malloc)
  TCB_t *tcb = (TCB_t*) malloc(sizeof(TCB_t));
  q_element *thread = NewItem();
  thread->payload = (void*) tcb;
  
  // call init_TCB with appropriate arguments
  init_TCB(tcb, function, stack, stack_size);
  
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
  swapcontext(&parent, &(((TCB_t*)(Curr_Thread->payload))->context)); // start the first round
  
};

void yield() // similar to run
{
  q_element *Prev_Thread;
  AddQueue(&ReadyQ, Curr_Thread);
  Prev_Thread = Curr_Thread;
  Curr_Thread = DelQueue(&ReadyQ);
  // swap the context, from Prev_Thread to the thread pointed to Curr_Thread
};

// Get ID of thread
int get_id (q_element *thread)
{
  return ((TCB_t*)(thread->payload))->thread_id;
};

#endif
