#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sem.h"
#include "threads.h"
#include "q.h"

int id (q_element *item)
{
  return *((int*)(item->payload));
}

// ID counter for unique items being added to the queue
int counter = 0;

// Global Queue of ints
q_element *Queue;

// Semaphore for items in queue
Semaphore_t *sem;

// Number of consumers and producers
int count_cons = 3;
int count_prod = 1;

// Easily modifiable function for sleep
void go_to_sleep()
{
  sleep(1);
}

// Consumer function to consume items from queue
void consumer (void *arg)
{
  int value = *(int*) arg;
  printf("Consumer C%02d created\n",value);
  while (1)
    {
      P(sem);
      q_element *item = DelQueue(&Queue);
      printf("C%02d: Consuming item %03d\n", value, id(item));
      // Free item
      free(item->payload);
      FreeItem(item);
      go_to_sleep();
    };
};

// Producer function to add items to queue
void producer (void *arg)
{
  int value = *(int*) arg;
  printf("Producer P%02d created\n",value);
  while (1)
    {
      printf("P%02d: Producing item %03d\n", value, counter);
      
      int *item_value = malloc(sizeof(int));
      q_element *item = NewItem();
      *item_value = counter;
      counter++;
      item->payload = (void*) item_value;

      AddQueue(&Queue, item);
      V(sem);
      go_to_sleep();
    };
};

int main (int argc, char *argv[])
{
  int i; // for loop variable

  // Get consumer count
  if (argc >= 2)
    {
      count_cons = atoi(argv[1]);
    }

  // Get producer count
  if (argc >= 3)
    {
      count_prod = atoi(argv[2]);
    }

  // Set array for indices
  int *indices_cons;
  int *indices_prod;
  indices_cons = (int*) malloc(count_cons * sizeof(int));
  indices_prod = (int*) malloc(count_prod * sizeof(int));
  for (i = 0; i < count_cons; i++)
    {
      *(indices_cons+i) = i;
    };
  for (i = 0; i < count_prod; i++)
    {
      *(indices_prod+i) = i;
    };

  // Setup semaphore
  sem = CreateSem(0);

  // Setup Queue
  Queue = NewQueue();

  // Setup Consumers first
  for (i = 0; i < count_cons; i++)
    {
      start_thread(consumer, (void*) (indices_cons+i));
    }

  // Setup Producers next
  for (i = 0; i < count_prod; i++)
    {
      start_thread(producer, (void*) (indices_prod+i));
    }
  
  run();
};
