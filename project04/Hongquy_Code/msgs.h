#include "sem.h"

typedef struct message message;
typedef struct port port;
typedef struct set set;

//message contains array of nums, and has next and prev
struct message{
	int nums[10];
	message* next;
	message* prev;
};

//port contains a queue of messages, a count to keep track of how many messages
//a semaphore to block sending, and another semaphore to block recieving
// and a mutex
struct port{
	message** messages;
	int count;	
	Semaphore_t* sendS;
	Semaphore_t* recieveS;
	int mutex;
};

struct set{
	port arrayP[100];
};

//function to initialize ports
port* initPort(){
	
	port* newP = (port*) malloc(sizeof(port));
	newP->messages = (message**) malloc(sizeof(message*));
	newP->count = 0;
	newP->mutex = 1;
	newP->sendS = CreateSem(1);
	newP->recieveS = CreateSem(1);

	return newP;
}

//This function when called will send the msg to the port specified
void send(port* Pt, message* msg){

	//check if mutex is available
	if(Pt->mutex == 1){
		
		Pt->mutex--;

		//if the buffer is full, then block
		if((Pt->count) >= 10){

			//since send will be blocked, give the mutex back
			Pt->mutex = Pt->mutex + 1;
			
			//block
			P(Pt->sendS);
		}

		//Cases to send message to the port and add it to the port's queue
		if( (Pt->messages) == NULL){
			printf("error, queue not made\n");
			exit(1);
		}

		else if( (*(Pt->messages)) == NULL ){
			*(Pt->messages) = msg;
			Pt->count++;
		}

		else if( (*(Pt->messages))->next == NULL){
			(*(Pt->messages))->next = msg;
			(*(Pt->messages))->prev = msg;
			msg->prev = *(Pt->messages);
			msg->next = *(Pt->messages);
			Pt->count++;
		}

		else if((*(Pt->messages))->next != NULL){
			message* tail = (*(Pt->messages))->prev;

			tail->next = msg;
			tail->next->next = *(Pt->messages);
			tail->next->prev = tail;
			(*(Pt->messages))->prev = tail->next;
			Pt->count++;
		}
		
		//give back mutex after sending the message
		Pt->mutex = Pt->mutex + 1;

		//unblock any reciving proccesses
		V(Pt->recieveS);
	}
}

//function to cause a server to recieve a message from a port
void recieve(port* Pt, message** msgR){
	
	//checks if the mutex is availiable 
	if(Pt->mutex == 1){
		
		Pt->mutex--;

		//if the buffer is empty, block the recieving process
		if(Pt->count <= 0){
			
			//Give back the mutex since this process will be blocked
			Pt->mutex++;

			//block
			P(Pt->recieveS);
		}
	
		//Cases to acquire the message from the port's queue
		if(*(Pt->messages) == NULL){
			printf("error, port empty\n");
			exit(1);
		}
		else if((*(Pt->messages))->next == NULL){
			*msgR = *(Pt->messages);
			*(Pt->messages) = NULL;
			Pt->count--;
		
		}
		else if((*(Pt->messages))->next != NULL && (*(Pt->messages))->next != (*(Pt->messages))){
			*msgR = *(Pt->messages);
			message* tail = (*(Pt->messages))->prev;
		
			tail->next = (*(Pt->messages))->next;
			(*(Pt->messages))->next->prev = tail;

			(*(Pt->messages)) = (*(Pt->messages))->next;
			Pt->count--;
		
	
		}
		else if((*(Pt->messages))->next !=NULL && (*(Pt->messages))->next == (*(Pt->messages))){
			*msgR = *(Pt->messages);
			*(Pt->messages) = NULL;
			Pt->count--;
		
		}
		
		//Give back the mutex		
		Pt->mutex++;

	}
	
}
