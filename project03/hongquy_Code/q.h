#ifndef Q_H
#define Q_H

#include <stdlib.h>
#include <stdio.h>
#include "TCB.h"

TCB_t* NewItem(){
	TCB_t* newPtr = (TCB_t*) malloc(sizeof(TCB_t));
	newPtr->next = NULL;
	newPtr->prev = NULL;
//	newPtr->thread_id = NULL;

	getcontext(&(newPtr->context));
	
	return newPtr;
}

TCB_t** newQueue(){
	TCB_t** head = (TCB_t**) malloc(sizeof(TCB_t*));
	return head;
}

void AddQueue(TCB_t** head, TCB_t* item){
	if(head == NULL){
		printf("error, queue not made\n");
		exit(1);
	}
	else if(*head == NULL ){
		item->prev = item;
		item->next = item;
		*head = item;
	}	
	else{
		item->next = (*head);
		item->prev = (*head)->prev;
		(*head)->prev->next = item;
		(*head)->prev = item;
	}
}

TCB_t* DelQueue(TCB_t** head){

	TCB_t* delEle = NULL;
	
	if((*head) == NULL){
		printf("error, queue empty\n");
		exit(1);
	}
	else if((*head)->next == NULL){
		delEle = *head;
		(*head) = NULL;
	///	printf("Item deleted 1\n");
	}
	else if((*head)->next != NULL && (*head)->next != (*head)){
		delEle = *head;
		TCB_t* tail = (*head)->prev;
		
		tail->next = (*head)->next;
		(*head)->next->prev = tail;

		(*head) = (*head)->next;
	//	printf("Item deleted 2\n");
	
	}
	else if((*head)->next !=NULL && (*head)->next == *head){
		delEle = *head;
		*head = NULL;
	//	printf("Item deleted 3\n");
	}

	return delEle;
	
}
#endif
