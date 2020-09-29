#include "q.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

	qElement** head = newQueue();
	qElement* item = NewItem();
	
	item->load = 2;
	AddQueue(head, item);
	
	item = NewItem();
	item->load = 3;
	AddQueue(head, item);

	printf("head value: %d\n", (*head)->load);

	printf("should be item 1 value : %d\n", (*head)->next->load);
	printf("should be item 2 value: %d\n", (*head)->prev->load);

	printf("should be item 2 value : %d\n", (*head)->next->next->load);

		
	qElement* delitem = DelQueue(head);
	
	printf("value should be 1: %d\n", delitem->load);
	
	delitem = DelQueue(head);
	
	printf(" value should be 2: %d\n", delitem->load);
	
	delitem = DelQueue(head);

	printf(" value should be 3: %d\n", delitem->load);

	DelQueue(head);
	return 1;	
}
