#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "threads.h"



typedef struct semaphore_t {
     pthread_mutex_t mutex;
     pthread_cond_t cond;
     int count;
} semaphore_t;

void init_sem(semaphore_t *s, int i)
{   
    s->count = i;
    pthread_mutex_init(&(s->mutex), NULL);
    pthread_cond_init(&(s->cond), NULL);
}


/*
 * The P routine decrements the semaphore, and if the value is less than
 * zero then blocks the process 
 */
void P(semaphore_t *sem)
{   
    pthread_mutex_lock (&(sem->mutex)); 
    sem->count--;
    if (sem->count < 0) pthread_cond_wait(&(sem->cond), &(sem->mutex));
    pthread_mutex_unlock (&(sem->mutex)); 
}


/*
 * The V routine increments the semaphore, and if the value is 0 or
 * negative, wakes up a process and yields
 */

void V(semaphore_t * sem)
{   
    pthread_mutex_lock (&(sem->mutex)); 
    sem->count++;
    if (sem->count <= 0) {
	pthread_cond_signal(&(sem->cond));
    }
    pthread_mutex_unlock (&(sem->mutex)); 
    pthread_yield();
}

int *x;
semaphore_t child_done;
semaphore_t parent_done;


int child (void *arg)
{
  int index = *(int*) arg;
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

  // Get number of children from command line
  int count = 3;
  if (argc >= 2)
    {
      count = atoi(argv[1]);
    }
  
  // Setup array for incrementing and indices
  int *indices;
  x = calloc(count, sizeof(int));
  indices = calloc(count, sizeof(int));
  for (i = 0; i < count; i++)
    {
    *(x+i) = 0;
    *(indices+i) = i;
    }

  // Initialize semaphores
  init_sem(&child_done,0);
  init_sem(&parent_done,0);

  // Setup and start pthreads
  pthread_t *pids;
  pids = calloc(count, sizeof(pthread_t));

  for (i = 0; i < count; i++)
    pids[i] = start_thread(child, (void*) (indices+i));

  int failure = 0;
  int j = 0;
  // Loop to wait for children then print
  while (1)
    {
      j = j + 1;
      
      // Wait for all children
      for (i = 0; i < count; i++)
        P(&child_done);
      
      // print out array
      for (i = 0; i < count; i++)
        {
          printf("i: %d, x[%d] = %d\n", j, i, *(x+i));
          if (j != *(x+i))
            {
              failure = 1;             
            }
          if ((i == count - 1) && failure)
            break;
        }
      
      if (failure)
        break;
          
      // Signal to children that parent is done
      for (i = 0; i < count; i++)
        V(&parent_done);

    }

}





