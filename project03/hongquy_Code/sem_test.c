#include "sem.h"

Semaphore_t* sem;

int global1 = 0;
int global2 = 0;
int global3 = 0;

void f1(){
	while(1){

		P(sem);
	
		printf("function 1 is running\n");
		
		sleep(1);

		global1++;
		
		printf("Global 1 value: %d\n", global1);
	
		V(sem);
	
//		printf("past V function\n");
		
		sleep(1);
	}
}

void f2(){
	while(1){
		P(sem);
	
		printf("function 2 is running\n");
		
		sleep(1);

		global2 = global2 + 2;

		printf("Global 2 value: %d\n", global2);
		V(sem);
	
//		printf("past V function\n");
       	
		sleep(1);
	}
}

void f3(){
	while(1){
		P(sem);
	
		printf("function 3 is running\n");
		sleep(1);

		global3 = global3 + 3;
	
		printf("Global 3 value: %d\n", global3);

		V(sem);

//		printf("past V function\n");
		
		sleep(1);
	}
}

TCB_t** ReadyQ;
TCB_t* Curr_Thread;

void main(){

	sem = CreateSem(2);
	ReadyQ = newQueue();
	Curr_Thread = NewItem();

	printf("This part works 1\n");

	start_thread(f1);
	start_thread(f2);
	start_thread(f3);

	printf("this part works 2\n");

	run();

}
