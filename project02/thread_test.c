// Matthew Berk
// Hongquy Nguyen
// CSE 521 - Distributed and Multiprocessor Operating Systems
// Project 02
// Due October 7, 2020

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "threads.h"

// Number of children functions to run
int count = 3;

// Global variable
int global = 0;

// Easily modifiable function for sleep
void go_to_sleep()
{
  sleep(1);
}

// Child function to have multiple copies running
void function (void *arg)
{
  int value = *(int*) arg;
  int local = 0;

  while (1)
    {
      printf("Function %02d: global = %d, local = %d\n", value, global, local);
      go_to_sleep();
      global++;
      local++;
      go_to_sleep();
      printf("Function %02d: incremented, global = %d, local = %d\n", value, global, local);
      go_to_sleep();
      yield();
    }
}

int main (int argc, char *argv[])
{
  int i; // for loop variable
  
  // Get number of children from command line
  if (argc >= 2)
    {
      count = atoi(argv[1]);
    }

  // Setup array for indices
  int *indices;
  indices = (int*) malloc(count * sizeof(int));
  for (i = 0; i < count; i++)
    {
      *(indices+i) = i;
    };

  // Setup different threads
  for (i = 0; i < count; i++)
    {
      start_thread(function, (void*) (indices+i));
    };

  run();
  
};
