// CSE 531 - Distributed and Multiprocessor Operating Systems
// Project 4
// Due November 11, 2020
// Matt Berk
// Hongquy Nguyen

#include "msgs.h"

//global ports
set* globalPorts;

void client1(){
    
    //Making a message. Message is 1111111111
    message* newMessage = (message*) malloc(sizeof(message));
    for (int i = 0; i < 10; i++){
        newMessage->nums[i] = 1; 
    }

    //Repeatedly sending the message
    while(1){
        printf("In client 1\n");
        sleep(1);
        send(&(globalPorts->arrayP[0]), newMessage);
    }
}

void client2(){
    //Making a message. Messages is 0123456789
    message* newMessage = (message*) malloc(sizeof(message));
    for (int i = 0; i < 10; i++){
        newMessage->nums[i] = i;
    }

    //Repeatedly sending the message
    while(1){
        printf("In client 2\n");
        sleep(1);
        send(&(globalPorts->arrayP[1]), newMessage);
    }

}

void server1(){
    //message to recieve
    message** recievedM = (message**) malloc(sizeof(message*));

    //Repeatedly read from port 0
    while(1){
        printf("In server 1\n");

        recieve(&(globalPorts->arrayP[0]), recievedM);
        
        sleep(1);
        
        //Printing the message from port 0
        printf("Printing message:\n");
        for(int i = 0; i < 10; i++){
            printf("%d", (*(recievedM))->nums[i]);
        }
        printf("\n");
        sleep(1);

        V((&(globalPorts->arrayP[0]))->sendS);
    }


}
void server2(){
    //message to recieve
    message** recievedM = (message**) malloc(sizeof(message*));
    
    //Repeatedly read from port 1
    while(1){

        printf("In server 2\n");
        recieve(&(globalPorts->arrayP[1]), recievedM);
        sleep(1);
        
        //printing the message from port 1
        printf("Printing message:\n");
        for(int i = 0; i < 10; i++){
            printf("%d", (*(recievedM))->nums[i]);
        }
        printf("\n");
        sleep(1);

        V((&(globalPorts->arrayP[1]))->sendS);
    }
}

//Declare globals
TCB_t** ReadyQ;
TCB_t* Curr_Thread;
int counterID;

void main(){
    //global ports
    globalPorts = (set*) malloc(sizeof(set));    

    //initialize all the ports
    for(int i = 0; i < 100; i++){
        globalPorts->arrayP[i] = *(initPort());
    }

    //Allocate memory to globals
    ReadyQ = newQueue();
    Curr_Thread = NewItem();
    counterID = 0; 
    
    start_thread(client1);
    start_thread(client2);
    start_thread(server1);
    start_thread(server2);
   
    run();
}
