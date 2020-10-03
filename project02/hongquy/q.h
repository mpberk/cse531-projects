#ifndef Q_H
#define Q_H

#include <stdlib.h>
#include <stdio.h>
#include "TCB.h"

TCB_t* NewItem(){
	TCB_t* newPtr = (TCB_t*) malloc(sizeof(TCB_t));
	newPtr->next = NULL;
	newPtr->prev = NULL;
	
	getcontext(&(newPtr->context));
//	newPtr->thread_id = -1;
	return newPtr;
}

TCB_t** newQueue(){
	TCB_t** head = (TCB_t**) malloc(sizeof(TCB_t*));
	(*head) = NewItem();
	return head;
}

void AddQueue(TCB_t** head, TCB_t* item){
	if(*head == NULL){
		printf("error, queue not made\n");
		exit(1);
	}
	else if((*head)->next == NULL){
		(*head)->next = item;
		(*head)->prev = item;
		item->prev = (*head);
		item->next = (*head);
		printf("Item added! 1\n");
	}
	else if((*head)->next != NULL){
		TCB_t* tail = (*head)->prev;

		tail->next = item;
		tail->next->next = (*head);
		tail->next->prev = tail;
		(*head)->prev = tail->next;
		printf("Item added! 2\n");
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
