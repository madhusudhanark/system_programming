#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int          x;
  struct Node *next;
};

struct Node *addElements(int number, struct Node *head)
{
  struct Node *current;

  if (number <= 0)
  {
    return head;
  }

  if (head == NULL)
  {
    head = malloc(sizeof(struct Node));
    printf("inside func head %p\n", head);
  }

  current = head;
  for (int i = 0; i < number - 1; i++)
  {
    current->next = malloc(sizeof(struct Node));
    printf("inside func current %p\n", current->next);

    current = current->next;
  }

  current->next = NULL;

  printf("inside func head %p\n", head);

  return head;
}

int main()
{
  struct Node *head = malloc(sizeof(struct Node));
  struct Node *curr;

  head = addElements(10, head);

  printf("outside func head %p\n", head);
  printf("outside func head->next %p\n", head->next);

  for (curr = head; curr != NULL; curr = curr->next)
  {
    printf("%p has %d\n", curr);
  }
}