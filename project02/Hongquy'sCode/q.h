#include <stdlib.h>
#include <stdio.h>
#include "TCB.h"

typedef struct qElement{
	struct qElement* next;
	struct qElement* prev;
	TCB_t* load;
} qElement;

qElement* NewItem(){
	qElement* newPtr = (qElement*) malloc(sizeof(qElement));
	newPtr->next = NULL;
	newPtr->prev = NULL;
	newPtr->load = NULL;
	return newPtr;
}

qElement** newQueue(){
	qElement** head = (qElement**) malloc(sizeof(qElement*));
	(*head) = NewItem();
	return head;
}

void AddQueue(qElement** head, qElement* item){
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
		qElement* trans = (*head)->prev;

		trans->next = item;
		trans->next->next = (*head);
		trans->next->prev = trans;
		(*head)->prev = trans->next;
		printf("Item added! 2\n");
	}
}

qElement* DelQueue(qElement** head){

	qElement* delEle = NULL;
	
	if((*head) == NULL){
		printf("error, queue empty\n");
		exit(1);
	}
	else if((*head)->next == NULL){
		delEle = *head;
		(*head) = NULL;
		printf("Item deleted 1\n");
	}
	else if((*head)->next != NULL && (*head)->next != (*head)){
		delEle = *head;
		qElement* temp = (*head)->prev;
		temp->next = (*head)->next;
		(*head)->next->prev = temp;
		(*head) = (*head)->next;
		printf("Item deleted 2\n");
	
	}
	else if((*head)->next !=NULL && (*head)->next == *head){
		delEle = *head;
		*head = NULL;
		printf("Item deleted 3\n");
	}

	return delEle;
	
}
