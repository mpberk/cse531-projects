#ifndef Q_H
#define Q_H

#include <stdio.h>
#include <stdlib.h>

typedef struct q_element q_element;

struct q_element
{
  q_element *prev;
  q_element *next;
  void* payload;
};

q_element *NewItem()
{
  q_element *new_item = (q_element*) malloc(sizeof(q_element));
  new_item->prev = NULL;
  new_item->next = NULL;
  return new_item;
};

void FreeItem(q_element *item)
{
  free(item);
};

q_element *NewQueue()
{
  q_element* head = NULL;
  return head;
};

// Add to end of queue
void AddQueue(q_element **head, q_element *item)
{
  if (*head == NULL)
    {
      printf("Hit AQ A\n");
      item->prev = item;
      item->next = item;
      *head = item;
    }
  else
    {
      printf("Hit AQ B\n");
      item->next = (*head);
      printf("Hit AQ C\n");
      item->prev = (*head)->prev;
      printf("Hit AQ D\n");
      (*head)->prev->next = item;
      printf("Hit AQ E\n");
      (*head)->prev = item;
      printf("Hit AQ F\n");
    };
  printf("Hit AQ G\n");
};

// Remove from head of queue
q_element *DelQueue(q_element **head)
{
  q_element *deleted_item;
  if (*head == NULL)
    {
      printf("ERROR: Attempted to delete item from empty queue\n");
    }
  else
    {
      deleted_item = *head;
      (*head)->next->prev = (*head)->prev;
      (*head)->prev->next = (*head)->next;
      *head = (*head)->next;
      deleted_item->next = NULL;
      deleted_item->prev = NULL;
    };
  return deleted_item;
};


#endif
