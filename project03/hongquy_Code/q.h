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
	
	if(*head == NULL){
		printf("error, queue empty\n");
		exit(1);
	}
	else{
		delEle = *head;
		(*head)->next->prev = (*head)->prev;
		(*head)->prev->next = (*head)->next;
		*head = (*head)->next;
		delEle->next = NULL;
		delEle->prev = NULL;
	}
	return delEle;
	
}
#endif
