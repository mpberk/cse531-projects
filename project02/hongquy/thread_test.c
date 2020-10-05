#ifndef THREAD_TEST
#define THREAD_TEST

#include "threads.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globVar = 0;

void function1(){
	int local = 0;

	while (1) {
		printf("In function 1\n");
		sleep(1);
		globVar++; local++;
		printf("global value: %d, local value: %d\n", globVar, local);
		printf("yielding in function 1\n\n");
		sleep(1);
		yield();
	}
}

void function2(){
	int local = 0;

	while(1) {
		printf("In function 2\n");
		sleep(1);
		globVar++; local++;
		printf("global value: %d, local value: %d\n", globVar, local);
		printf("yielding in function 2\n\n");
		sleep(1);
		yield();
	}

}

void function3(){

	int local = 0;

	while(1) {

		printf("In function 3\n");
		sleep(1);
		globVar++; local++;
		printf("global value: %d, local value: %d\n", globVar, local);
		printf("yielding in function 3\n\n");
		sleep(1);
		yield();
	}
}

TCB_t** ReadyQ;
TCB_t* Curr_Thread;

int main(){

  ReadyQ = newQueue();

//	printf("this part works 1\n");

	start_thread(function1);
	start_thread(function2);
	start_thread(function3);

//	printf("this part works 2\n");
	run();
	return 1;
}

#endif
