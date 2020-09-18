#ifndef Q_H
#define Q_H

#include <stdio.h>
#include <stdlib.h>

typedef struct q_element q_element;

struct q_element
{
  q_element *prev;
  q_element *next;
  int payload;
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

void AddQueue(q_element **head, q_element *item)
{
  if (*head == NULL)
    {
      printf("Queue is empty\n");
      item->prev = item;
      item->next = item;
    }
  else
    {
      printf("Queue is not empty\n");
      item->next = (*head);
      item->prev = (*head)->prev;      
      (*head)->prev = item;
      (*head)->prev->next = item;
    };
  
  *head = item;
  
};

#endif
