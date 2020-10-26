#include "sem.h"

Semaphore_t* r_sem;
Semaphore_t* w_sem;

int mutex;

int rwc = 0, wwc = 0, rc = 0, wc = 0, global_ID = 0;

void reader_entry(int ID){
	printf("reader #%d trying to read\n" , ID);
	if(mutex == 1){

		printf("In reader_entry mutex\n");
		
		mutex = 0;
		
		if(wwc > 0 || wc > 0) {
			printf("reader #%d is being blocked\n", ID);
			rwc++;
			mutex = 1;
			P(r_sem);
			rwc--;	     
		}
		printf("Reader count increased\n");
		rc++;
		if (rwc > 0) {
			printf("Releasing waiting readers\n");
			V(r_sem);
		}
		else{
			printf("No readers waiting, release mutex\n");
			mutex = 1;
		}
	}
}

void reader_exit(int ID){
	if(mutex == 1){
		printf("In reader_exit mutex\n");
		mutex = 0;
		
		printf("Reducing reader count\n");

		rc--;
		
		if(rc == 0 && wwc > 0) {
			printf("Releasing waiting writers if there are no readers\n");
			V(w_sem);
		}
		else{
			printf("Releasing mutex\n");
			mutex = 1;
		}

	}
}

void writer_entry(int ID){
	
	printf("writer %d is trying to write\n", ID);
	if (mutex == 1) {
		printf("In writer_entry mutex\n");
		
		mutex = 0;
		
		if( rc > 0 || wc > 0){
			printf("writer %d is being blocked\n", ID);
			wwc++;
			mutex = 1;
			P(w_sem);
			wwc--;
		}
		printf("Increasing writer count\n");

		wc++;
		mutex = 1;

	}
}

void writer_exit(int ID){

	if (mutex == 1) {
		printf("In writer exit mutex\n");
		mutex = 0;

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
		else {
			printf("Releasing mutex\n");
			mutex = 1;
		}
	}
}

void reader(){
	printf("In reader function\n");
	printf("Thread running rn is: %d\n", (*ReadyQ)->thread_id);
	int ID;
	if(mutex == 1){
		printf("In mutex\n");
		mutex = 0;
		ID = global_ID;
		global_ID++;
		mutex = 1;
	}
	while(1){
		printf("In reader loop\n");
		reader_entry(ID);
		printf("Reader #%d is running\n" , ID);
		sleep(1);
		reader_exit(ID);
	}
}

void writer(){
	printf("In writer function");
	int ID;
	if (mutex == 1) {
		printf("In mutex\n");
		mutex = 0;
		ID = global_ID;
		global_ID++;
		mutex = 1;
	}
	while (1){
		printf("In writer loop\n");
		writer_entry(ID);
		printf("Writer #%d is running\n", ID);
		sleep(1);
		writer_exit(ID);
	}

}

TCB_t** ReadyQ;
TCB_t* Curr_Thread;
int counterID;
void main(){

	w_sem = CreateSem(0);
	r_sem = CreateSem(0);
	mutex = 1;

	ReadyQ = newQueue();
	Curr_Thread = NewItem();
	counterID = 0;

	printf("This part works 1\n");

	start_thread(reader);
	start_thread(reader);
	
	printf("ReadyQ->next: %d \n", (*ReadyQ)->next->thread_id);

	start_thread(reader);
	start_thread(reader);
	
	printf("ReadyQ->next->next: %d \n", (*ReadyQ)->next->next->thread_id);

	start_thread(writer);
	start_thread(writer);

	printf("this part works 2\n");

	run();
	
}
