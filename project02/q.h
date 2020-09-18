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
      item->prev = item;
      item->next = item;
    }
  else
    {
      item->next = (*head);
      item->prev = (*head)->prev;
      (*head)->prev->next = item;
      (*head)->prev = item;
    };

  *head = item;

};

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
