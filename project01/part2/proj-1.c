#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

int *x;
semaphore_t child_done;
semaphore_t parent_done;


int child (void *arg)
{
  int index = (int) arg;
  while (1)
    {
      // Increment specific array entry
      *(x+index) = *(x+index) + 1;
      // Signal child is done
      V(&child_done);
      // Wait for parent
      P(&parent_done);
    }
}

int main(int argc, char *argv[])
{
  int i;
  int j;

  // Get number of children from command line
  int count = 3;
  if (argc >= 2)
    {
      count = atoi(argv[1]);
    }

  // Setup array
  x = calloc(count, sizeof(int));
  for (i = 0; i < count; i++)
    *(x+i) = 0;

  // Initialize semaphores
  init_sem(&child_done,0);
  init_sem(&parent_done,0);
    
  // Setup and start pthreads
  pthread_t *pids;
  pids = calloc(count, sizeof(pthread_t));

  for (i = 0; i < count; i++)
    pids[i] = start_thread(child, (void*) i);
  
  // Loop to wait for children then print
  for (j = 0; j < 10000000; j++)
    {
      // Wait for all children
      for (i = 0; i < count; i++)
        P(&child_done);

      // print out array
      for (i = 0; i < count; i++)
        printf("i: %d, x[%d] = %d\n", j, i, *(x+i));

      // Signal to children that parent is done
      for (i = 0; i < count; i++)
        V(&parent_done);

    }

}





