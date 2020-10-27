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

	printf("Reader count increased\n");
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
	printf("Increasing writer count\n");

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

	printf("In reader function\n");
	
	int ID;
	
	ID = global_ID;
	global_ID++;
	
	while(1){
		printf("In reader loop\n");
		
		printf("Thread running rn is: %d\n", (*ReadyQ)->thread_id);
		printf("Next thread is: %d\n", (*ReadyQ)->next->thread_id);

		P(r_sem);

		reader_entry(ID);
		
		printf("Reader #%d is running\n" , ID);
		sleep(1);
		
		reader_exit(ID);

		V(r_sem);
	}
}

void writer(){
	
	printf("In writer function\n");
	
	int ID;
	
	ID = global_ID;
	global_ID++;
	
	while (1){
		printf("In writer loop\n");
		
		printf("Thread running rn is: %d\n", (*ReadyQ)->thread_id);
		printf("Next thread is: %d\n", (*ReadyQ)->next->thread_id);

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

//	printf("ReadyQ: %d\n", (*ReadyQ)->thread_id);
//	printf("ReadyQ->next: %d \n", (*ReadyQ)->next->thread_id);
//	printf("ReadyQ->next->next: %d \n", (*ReadyQ)->next->next->thread_id);
//	printf("ReadyQ->-next->next->next: %d\n", (*ReadyQ)->next->next->next->thread_id);
	
	printf("this part works 2\n");
	run();
	
}
