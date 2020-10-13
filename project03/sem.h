#ifndef SEM_H
#define SEM_H

#include "threads.h"

typedef struct Semaphore_t
{
  int counter;
  q_element *Queue;
} Semaphore_t;

Semaphore_t *CreateSem(int InputValue)
{
  // mallocs a semaphore structure, initializes it to the InitValue and returns the pointer to the semaphore
};

void P(Semaphore_t * sem)
{
  // takes a pointer to a semaphore and performs P, i.e. decrements the semaphore, and if the value is less than zero then blocks the thread in the queue associated with the semaphore
};

void V(Semaphore_t * sem)
{
  // increments the semaphore, and if the value is 0 or negative, then takes a PCB out of the semaphore queue and puts it into the ReadyQ
  // Note: The V routine also "yields" to the next runnable thread
};

#endif
