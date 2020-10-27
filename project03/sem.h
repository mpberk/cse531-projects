#ifndef SEM_H
#define SEM_H

#include "threads.h"

typedef struct Semaphore_t
{
  int counter;
  q_element *Queue; // Queue of TCB_t's
} Semaphore_t;

Semaphore_t *CreateSem(int InputValue)
{
  // Mallocs a semaphore structure
  Semaphore_t* newSem = (Semaphore_t*) malloc(sizeof(Semaphore_t));
  // initializes it to the InitValue
  newSem->counter = InputValue;
  // initialize Queue
  newSem->Queue = NewQueue();
  // returns the pointer to the semaphore
  return newSem;

};

void P(Semaphore_t * sem)
{
  printf("P() was called\n");
  // decrements the semaphore
  sem->counter--;
  // if the value is less than zero, then blocks the thread in the queue associated with the semaphore
  // Note: This is very similar to yield, but adds Prev_Thread to sem's queue instead
  if (sem->counter < 0) {
    printf("Hit C. Sem is at: %d\n",sem->counter);
    q_element *Prev_Thread;
    // Store the current context in the sem queue
    AddQueue(&(sem->Queue), Curr_Thread);
    // Grab next thread in global queue
    Prev_Thread = Curr_Thread;
    Curr_Thread = DelQueue(&ReadyQ);
    // Swap contexts
    swapcontext(get_context_ptr(Prev_Thread), get_context_ptr(Curr_Thread));
  };
};

void V(Semaphore_t * sem)
{
  printf("V() was called\n");
  // increments the semaphore
  sem->counter++;
  // if the value is 0 or negative, then takes a TCB out the semaphore queue puts it into the ReadyQ
  // Note: If counter is less than 0, then a TCB must exist in the queue
  if (sem->counter <= 0)
    {
      printf("Hit V A. Sem is at: %d\n",sem->counter);
      // Get TCB_t from queue
      q_element *threadToAdd = DelQueue(&(sem->Queue));
      // Add to global queue to be run
      printf("Hit V B\n");
      AddQueue(&ReadyQ, threadToAdd);
    };
  // Note: The V routine also "yields" to the next runnable thread
  printf("Hit V C\n");
  yield();
  ;
};

#endif
