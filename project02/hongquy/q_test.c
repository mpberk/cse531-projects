#include <stdio.h>
#include <stdlib.h>

#include "q.h"

//int id (q_element *item)
//{
//  return *((int*)(item->payload));
//}

TCB_t** ReadyQ;
TCB_t* Curr_Thread;

int main(int argc, char *argv[])
{

  printf("Creating queue\n");
  ReadyQ = newQueue();
  // ReadyQ at this point should be {head}

  printf("Creating item1\n");
  TCB_t *item1 = NewItem();

  printf("Adding item1 to queue\n");
  AddQueue(ReadyQ, item1);
  // ReadyQ at this point should be {head,item1}

  // The head item should have both next and prev pointers point to item1
  if (((*ReadyQ)->next != item1) || ((*ReadyQ)->prev != item1))
    printf("ERROR: Failed to setup next and prev pointers for head\n");

  // The item1 should have next and prev point to head
  if ((item1->next != (*ReadyQ)) || (item1->prev != (*ReadyQ)))
    printf("ERROR: Failed to setup next and prev pointers for item1\n");
  
  printf("Creating item2\n");
  TCB_t *item2 = NewItem();

  printf("Adding item2 to queue\n");
  AddQueue(ReadyQ, item2);
  // ReadyQ at this point should be {head,item1,item2}

  // The head item should have next to item1 and prev to item2
  if (((*ReadyQ)->next != item1) || ((*ReadyQ)->prev != item2))
    printf("ERROR: Failed to setup pointers for head\n");
  
  // The item1 should have next to item2 and prev to head
  if ((item1->next != item2) || (item1->prev != (*ReadyQ)))
    printf("ERROR: Failed to setup pointers for item1\n");

  // The item2 should have next to head and prev to item1
  if ((item2->next != (*ReadyQ)) || (item2->prev != item1))
    printf("ERROR: Failed to setup pointers for item2\n");

  printf("Creating item3\n");
  TCB_t *item3 = NewItem();

  printf("Adding item3 to queue\n");
  AddQueue(ReadyQ, item3);
  // ReadyQ at this point should be {head,item1,item2,item3}

  // The head item should have next to item1 and prev to item3
  if (((*ReadyQ)->next != item1) || ((*ReadyQ)->prev != item3))
    printf("ERROR: Failed to setup pointers for head\n");
  
  // The item1 should have next to item2 and prev to head
  if ((item1->next != item2) || (item1->prev != (*ReadyQ)))
    printf("ERROR: Failed to setup pointers for item1\n");
      
  // The item2 should have next to item3 and prev to item1
  if ((item2->next != item3) || (item2->prev != item1))
    printf("ERROR: Failed to setup pointers for item2\n");
      
  // The item3 should have next to head and prev to item2
  if ((item3->next != (*ReadyQ)) || (item3->prev != item2))
    printf("ERROR: Failed to setup pointers for item3\n");

  // Delete item from queue
  printf("Deleting item from queue\n");
  TCB_t *item1_deleted = DelQueue(ReadyQ);
  // ReadyQ at this point should be {head,item2,item3}
  
  // The head item should have next to item2 and prev to item3
  if (((*ReadyQ)->next != item2) || ((*ReadyQ)->prev != item3))
    printf("ERROR: Failed to setup pointers for head\n");
      
  // The item2 should have next to item3 and prev to head
  if ((item2->next != item3) || (item2->prev != (*ReadyQ)))
    printf("ERROR: Failed to setup pointers for item2\n");
      
  // The item3 should have next to head and prev to item2
  if ((item3->next != (*ReadyQ)) || (item3->prev != item2))
    printf("ERROR: Failed to setup pointers for item3\n");

  // Adding item1 back to queue
  printf("Adding item1 back to queue\n");
  AddQueue(ReadyQ, item1);
  // ReadyQ at this point should be {head,item2,item3,item1}

  // The head item should have next to item2 and prev to item1
  if (((*ReadyQ)->next != item2) || ((*ReadyQ)->prev != item1))
    printf("ERROR: Failed to setup pointers for head\n");
  
  // The item1 should have next to head and prev to item3
  if ((item1->next != (*ReadyQ)) || (item1->prev != item3))
    printf("ERROR: Failed to setup pointers for item1\n");
      
  // The item2 should have next to item3 and prev to head
  if ((item2->next != item3) || (item2->prev != (*ReadyQ)))
    printf("ERROR: Failed to setup pointers for item2\n");
      
  // The item3 should have next to item1 and prev to item2
  if ((item3->next != item1) || (item3->prev != item2))
    printf("ERROR: Failed to setup pointers for item3\n");

};

