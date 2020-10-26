#include "sem.h"

Semaphore_t* r_sem;
Semaphore_t* w_sem;

int mutex = 1;

int rwc = 0, wwc = 0, rc = 0, wc = 0, global_ID = 0;

void reader_entry(int ID){
	printf("reader #%d trying to read" , ID);
	if(mutex == 1){
		mutex = 0;
		if(wwc > 0 || wc > 0) {
			printf("reader #%d is being blocked", ID);
			rwc++;
			mutex = 1;
			P(r_sem);
			rwc--;	     
		}
		rc++;
		if (rwc > 0) {
			V(r_sem);
		}
		else{
			mutex = 1;
		}
	}
}

void reader_exit(int ID){
	if(mutex == 1){
		mutex = 0;
		rc--;
		if(rc == 0 && wwc > 0) {
			V(w_sem);
		}
		else{
			mutex = 1;
		}

	}
}

void writer_entry(int ID){
	
	printf("writer %d is trying to write", ID);
	if (mutex == 1) {
		
		mutex = 0;
		
		if( rc > 0 || wc > 0){
			printf("writer %d is being blocked", ID);
			wwc++;
			mutex = 1;
			P(w_sem);
			wwc--;
		}

		wc++;
		mutex = 1;
	}
}

void writer_exit(int ID){
	if (mutex == 1) {
		mutex = 0;
		wc--;
		if (rwc > 0) {
			V(r_sem);
		}
		else if( wwc > 0) {
			V(w_sem);
		}
		else {
			mutex = 1;
		}
	}
}

void reader(){
	int ID;
	if(mutex == 1){
		mutex = 0;
		ID = global_ID;
		global_ID++;
		mutex = 1;
	}
	while(1){
		reader_entry(ID);
		printf("Reader #%d", ID);
		sleep(1);
		reader_exit(ID);
	}
}

void writer(){
	int ID;
	if (mutex == 1) {
		mutex = 0;
		ID = global_ID;
		global_ID++;
		mutex = 1;
	}
	while (1){
		writer_entry(ID);
		printf("Writer #%d is running", ID);
		sleep(1);
		writer_exit(ID);
	}

}

TCB_t** ReadyQ;
TCB_t* Curr_Thread;

void main(){

	w_sem = CreateSem(1);
	r_sem = CreateSem(3);
	mutex = 1;

	ReadyQ = newQueue();
	Curr_Thread = NewItem();

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
