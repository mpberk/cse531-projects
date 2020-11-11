// CSE 531 - Distributed and Multiprocessor Operating Systems
// Project 3
// Due October 26, 2020
// Matt Berk
// Hongquy Nguyen

#include "sem.h"

Semaphore_t* r_sem;
Semaphore_t* w_sem;

int rwc = 0, wwc = 0, rc = 0, wc = 0, global_ID = 0;

void reader_entry(int ID){

	printf("reader #%d trying to read\n" , ID);
		
	if(wwc > 0 || wc > 0) {
		printf("reader #%d is being blocked\n", ID);
		rwc++;
		P(r_sem);
		rwc--;	     
	}

	rc++;

	if (rwc > 0) {
		printf("Releasing waiting readers\n");
		V(r_sem);
	}
	sleep(1);
}

void reader_exit(int ID){
		
	printf("Reducing reader count\n");
	rc--;
		
	if(rc == 0 && wwc > 0) {
		printf("Releasing waiting writers if there are no readers\n");
		V(w_sem);
	}
	sleep(1);
}

void writer_entry(int ID){
	
	printf("writer %d is trying to write\n", ID);		
	
	if( rc > 0 || wc > 0){
		printf("writer %d is being blocked\n", ID);
		wwc++;
		P(w_sem);
		wwc--;
	}

	wc++;
	sleep(1);
}

void writer_exit(int ID){

	printf("decreasing writer count\n");
	wc--;
		
	if (rwc > 0) {
		printf("If there are waiting readers, release them\n");
		V(r_sem);
	}
	else if( wwc > 0) {
		printf("Releasing any waiting writers if there are no waiting readers\n");
		V(w_sem);
	}
}

void reader(){
	
	int ID;
	
	ID = global_ID;
	global_ID++;
	
	while(1){

		P(r_sem);

		reader_entry(ID);
		
		printf("Reader #%d is running\n" , ID);
		sleep(1);
		
		reader_exit(ID);

		V(r_sem);
	}
}

void writer(){
	
	int ID;
	
	ID = global_ID;
	global_ID++;
	
	while (1){

		P(w_sem);

		writer_entry(ID);
		printf("Writer #%d is running\n", ID);
		sleep(1);
		writer_exit(ID);
		
		V(w_sem);
	}

}

TCB_t** ReadyQ;
TCB_t* Curr_Thread;
int counterID;

void main(){
	//printf("This is up to date\n");
	
	w_sem = CreateSem(1);
	r_sem = CreateSem(1);
	
	ReadyQ = newQueue();
	Curr_Thread = NewItem();
	counterID = 0;

	printf("This part works 1\n");

	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	

	start_thread(writer);
	start_thread(writer);
	
	printf("this part works 2\n");
	run();
	
}
