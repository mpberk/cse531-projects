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

  // Resulting queue should be 1
  if (head != item1)
    printf("ERROR: Failed to add item1 to empty queue\n");

  if ((head->next != head) || (head->prev != head))
    printf("ERROR: Failed to setup next and prev pointers for queue with 1 item\n");

  printf("Creating item2\n");
  q_element *item2 = NewItem();
  item2->payload = 2;

  printf("Adding item2 to queue\n");
  AddQueue(&head, item2);

  // Resulting queue should be 2->1
  if (head != item2)
    printf("ERROR: Failed to add item2 to queue\n");

  if (head->next != item1)
    printf("ERROR: Failed to setup head->next pointer. Exp: %d, Act: %d\n",item1->payload,head->next->payload);

  if (head->prev != item1)
    printf("ERROR: Failed to setup head->prev pointer. Exp: %d, Act: %d\n",item1->payload,head->prev->payload);

  q_element *item3 = NewItem();
  item3->payload = 3;

  printf("Adding item3 to queue\n");
  AddQueue(&head, item3);

  // Resulting queue should be 3->2->1
  if (head->next != item2)
    printf("ERROR: Failed to setup head->next pointer. Exp: %d, Act: %d\n",item2->payload,head->next->payload);

  if (head->prev != item1)
    printf("ERROR: Failed to setup head->prev pointer. Exp: %d, Act: %d\n",item1->payload,head->prev->payload);

  printf("Removing item3 from queue\n");
  q_element *item3_removed = DelQueue(&head);

  // Resulting queue should be 2->1
  if (item3_removed != item3)
    printf("ERROR: Removed incorrect item");

  if (head != item2)
    printf("ERROR: New head is incorrect. Exp: %d, Act: %d",item2->payload,head->payload);

  if (head->next != item1)
    printf("ERROR: Failed to setup head->next pointer. Exp: %d, Act: %d\n",item1->payload, head->next->payload);

  if (head->prev != item1)
    printf("ERROR: Failed to setup head->prev pointer. Exp: %d, Act: %d\n",item1->payload, head->prev->payload);

  printf("Removing item2 from queue\n");
  q_element *item2_removed = DelQueue(&head);

  // Resulting queue should be 1
  if (item2_removed != item2)
    printf("ERROR: Removed incorrect item");

  if (head != item1)
    printf("ERROR: New head is incorrect. Exp: %d, Act: %d",item1->payload,head->payload);
  
};
