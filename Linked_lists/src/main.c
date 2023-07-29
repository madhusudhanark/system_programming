#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int          x;
  struct Node *next;
};

void addElements(int number, struct Node *head)
{
  struct Node *current;
  // if (number <= 0)
  // {
  //   return head;
  // }

  if (head == NULL)
  {
    // head = malloc(sizeof(struct Node));
    printf("inside func: head addr =  %p\n", head);
    scanf("%d", &head->x);
  }

  current = head;
  scanf("%d", &head->x);
  for (int i = 0; i < number - 1; i++)
  {
    current->next = malloc(sizeof(struct Node));
    printf("inside func:current addr =  %p\n", current->next);
    scanf("%d", &current->next->x);
    current = current->next;
  }

  current->next = NULL;

  printf("inside func: head  addr = %p\n", head);

  // return head;
}

struct Node *reverse_list(struct Node *head)
{
  struct Node *now, *pre;
  pre = head;
  now = pre->next;

  if (now->next == NULL)
  {
    pre->next  = NULL;
    head       = now;
    head->next = pre;
    return head;
  }
  else
  {
    struct Node *next_temp;
    next_temp = now->next;
    // head->next = NULL;
    pre->next = NULL;
    while (next_temp->next != NULL)
    {
      now->next = pre;
      pre       = now;
      now       = next_temp;
      next_temp = next_temp->next;
    }
    if (next_temp->next == NULL)
    {
      next_temp->next = now;
      now->next       = pre;
      head            = next_temp;
      printf("return addr head %p\n", head);
      return head;
    }
  }
}

void delete_list(int del_val, struct Node *head)
{
  struct Node *current;
  struct Node *prev;
  struct Node *next;

  current = head;
  // if (current->x = del_val) {}
  do
  {
    if (current->next->x = del_val)
    {
      struct Node *temp = current->next->next;
      free(current->next);
      current->next = temp;
    }
  } while (current->next != NULL);
}

int main()
{
  struct Node *head = malloc(sizeof(struct Node));
  printf("inside main : head addr =  %p \n", head);
  struct Node *curr;
  addElements(5, head);

  // printf("inside main : %p\n", head);
  // printf("outside func head->next %p\n", head->next);
  curr = reverse_list(head);
  head = curr;
  delete_list(4, head);
  while (curr != NULL)
  {
    printf("%p has %d\n", curr, curr->x);
    curr = curr->next;
  }

  return 0;
}