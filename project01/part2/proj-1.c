// CSE 531 - Distributed and Multiprocessor Operating Systems
// Project 1
// Due September 23, 2020
// Matt Berk
// Hongquy Nguyen
//
// Features:
//   Program runs without any parameters, but can take 1 argument for specifying the number of children running (default 3)
//   Semaphore synchronization scheme based on the solution to the Readers-Writers semaphore problem.
//   If the synchronization scheme fails, the program halts.
//
// Program description:
//   Main (parent) thread sets up array and semaphores
//   Parent creates 3 children
//   One of the children runs and starts the other children (using the start_children semaphore)
//   Once all of the children finish running (child_wait semaphore), the parent thread is started (start_parent semaphore)
//   Once the parent thread finishes running, the children are started
//   The process then repeats



#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

int count = 3;
int *x;
int active_children = 0;

semaphore_t mutex; // General mutex for critical sections
semaphore_t start_children; // Start a child
semaphore_t start_parent; // Start the parent
semaphore_t child_wait; // Children waiting for other children to finish up

int child (void *arg)
{
  int index = *(int*) arg;
  while (1)
    {
      // Wait for signal to start children
      P(&start_children);

      // Critical section
      P(&mutex);

      // Increase number of active children
      active_children++;

      // Allow other children to start if still more left
      if (active_children < count)
        V(&start_children);

      V(&mutex);

      // Increment specific array entry
      *(x+index) = *(x+index) + 1;

      // Critical section
      P(&mutex);

      // On last child
      if (active_children == count)
        {
          // Continue all children
          V(&child_wait);
          active_children--;
        }

      V(&mutex);

      // Wait until all children are done
      P(&child_wait);

      // Critical section
      P(&mutex);

      // On all but last child
      if (active_children != 0)
        {
          // End another child (violent sounding...)
          V(&child_wait);
          active_children--;
        }
      else
        {
          // On last child, start parent
          V(&start_parent);
        }

      V(&mutex);
    }
}

int main(int argc, char *argv[])
{
  int i;

  // Get number of children from command line
  if (argc >= 2)
    {
      count = atoi(argv[1]);
    }

  // Setup array for incrementing and indices
  int *indices;
  x = calloc(count, sizeof(int));
  indices = (int*) malloc(count * sizeof(int));
  for (i = 0; i < count; i++)
    {
      *(indices+i) = i;
    }

  // Initialize semaphores
  init_sem(&mutex,1);
  init_sem(&start_children,1);
  init_sem(&start_parent,0);
  init_sem(&child_wait,0);

  // Setup and start pthreads
  pthread_t *pids;
  pids = (pthread_t*) malloc(count * sizeof(pthread_t));

  for (i = 0; i < count; i++)
    pids[i] = start_thread(child, (void*) (indices+i));

  int failure = 0;
  int j = 0;
  // Loop to wait for children then print
  while (1)
    {
      j = j + 1;

      // Wait for start_parent from children finishing up
      P(&start_parent);

      // print out array
      for (i = 0; i < count; i++)
        {
          printf("i: %d, x[%d] = %d\n", j, i, *(x+i));

          // On failure of semaphores, break from loop and end program
          if (j != *(x+i))
            failure = 1;
          if ((i == count - 1) && failure)
            break;
        }

      if (failure)
        break;

      // Start children
      V(&start_children);
    }
}
