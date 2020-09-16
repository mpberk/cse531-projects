#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

pthread_t startThread(void* func, int* arg){
	pthread_t threadID;
	int rc;
	printf("\nIn main: creating thread\n");
	rc = pthread_create(&threadID, NULL, func, arg);
	if(rc){
		printf("Error, return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	return(threadID);
}

typedef struct semaphore_t {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int count;
} semaphore_t;

void init_sem(semaphore_t* s, int i){
	s->count = i;
	pthread_mutex_init(&(s->mutex), NULL);
	pthread_cond_init(&(s->cond), NULL);
}

void P(semaphore_t* sem){
	pthread_mutex_lock(&(sem->mutex));
	sem->count--;
	if(sem->count < 0){
		pthread_cond_wait(&(sem->cond), &(sem->mutex));
	}
	pthread_mutex_unlock(&(sem->mutex));
}

void V(semaphore_t* sem){
	pthread_mutex_lock (&(sem->mutex));
	sem->count++;
	if(sem->count <= 0) {
		pthread_cond_signal(&(sem->cond));
	}
	pthread_mutex_unlock(&(sem->mutex));
	pthread_yield(NULL);
}

semaphore_t mutex;
int childNum[3] = {0,0,0};

void child1(void){
	while(1){
		P(&mutex);
		printf("This is child1 start\n");
		childNum[0] = childNum[0] + 1;
		printf("This is end of child1\n");
		sleep(1);
		V(&mutex);
	}
	
}
void child2(void){

	while(1){
		P(&mutex);
		printf("This is child2 start\n");
		childNum[1] = childNum[1] + 1;
		printf("This is end of child2\n");
		sleep(1);
		V(&mutex);
	}
}
void child3(void){

	while(1){
		P(&mutex);
		printf("This is child3 start\n");
		childNum[2] = childNum[2] + 1;
		printf("This is end of child3\n");
		sleep(1);
		V(&mutex);
	}
}

int main(){
	
	init_sem(&mutex, 1);
	
	startThread(child1, NULL);
	startThread(child2, NULL);
	startThread(child3, NULL);

	sleep(1);	
	while (1){
		P(&mutex);
		printf("value 1: %d\n value 2: %d\n value 3: %d\n\n",childNum[0],childNum[1], childNum[2]);
		V(&mutex);
	}
	return 0;
}
