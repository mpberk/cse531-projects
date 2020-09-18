#include <stdio.h>
#include <stdlib.h>

#include "q.h"

int main(int argc, char *argv[])
{
  printf("Creating queue\n");
  q_element *head = NewQueue();

  printf("Creating item1\n");
  q_element *item1 = NewItem();

  printf("Freeing item1\n");
  FreeItem(item1);

  printf("Creating item1\n");
  item1 = NewItem();
  
  printf("Updating payload of item1\n");
  item1->payload = 1;

  printf("Adding item1 to queue\n");
  AddQueue(&head, item1);

  if (head != item1)
    printf("ERROR: Failed to add item1 to empty queue\n");

  if ((head->next != head) || (head->prev != head))
    printf("ERROR: Failed to setup next and prev pointers for queue with 1 item\n");
    
  printf("Creating item2\n");
  q_element *item2 = NewItem();
  item2->payload = 2;

  printf("Adding item to queue\n");
  AddQueue(&head, item2);

  if (head != item2)
    printf("ERROR: Failed to add item2 to queue\n");

  if (head->next != item1)
    printf("ERROR: Failed to setup head->next pointer. Exp: %d, Act: %d\n",item1->payload,head->next->payload);
  
  if (head->prev != item1)
    printf("ERROR: Failed to setup head->prev pointer. Exp: %d, Act: %d\n",item1->payload,head->prev->payload);
};
