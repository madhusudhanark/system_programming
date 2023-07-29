#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int          x;
  struct Node *next;
};

struct Node1
{
  int           x;
  struct Node1 *next;
  struct Node1 *pre;
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

  current = head;
  while (current->x = del_val)
  {
    struct Node *temp = current->next;
    free(current);
    current = temp;
  }

  while (current->next != NULL)
  {
    if (current->next->x == del_val)
    {
      struct Node *temp = current->next->next;
      free(current->next);
      current->next = temp;

      printf("%p\n%p\n", current, current->next);
    }
    current = current->next;
  }
}
int DL_addelements(int number, struct Node1 *dlhead)
{
  struct Node1 *current;
  current = dlhead;
  printf("current->next = %p\n", current->next);
  while (current->next != NULL)
  {
    current = current->next;
  }

  for (int i = 0; i < number - 1; i++)
  {
    current->next = malloc(sizeof(struct Node1));
    printf("current->previous = %p,current :%p,current->next:%p\n", current->pre, current, current->next);
    scanf("%d", &current->next->x);
    current->next->pre = current;
    current            = current->next;
  }
  return 0;
}

int main()
{
  struct Node * head   = malloc(sizeof(struct Node));
  struct Node1 *dlhead = malloc(sizeof(struct Node1));

  // printf("inside main : head addr =  %p \n", head);
  struct Node1 *curr;
  // addElements(5, head);
  DL_addelements(2, dlhead);
  DL_addelements(2, dlhead);

  // printf("inside main : %p\n", head);
  // printf("outside func head->next %p\n", head->next);
  // curr = reverse_list(head);
  curr = dlhead;
  // delete_list(4, head);//pass the value to be deleted from the linked list
  while (curr != NULL)
  {
    printf("%p has %d\n", curr, curr->x);
    curr = curr->next;
  }

  return 0;
}