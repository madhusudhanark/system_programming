#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
  int data;
  struct node * next;
}node;

void push(node** head,int data)
{
  node* new = malloc(sizeof(node));
  new->data = data;
  new->next = NULL;
  node* current = *head;
  if(*head == NULL)
  {
    *head = new;
    printf(" the new element assigned to head\n");
  }
  else
  {
    while(current->next != NULL)
  {
    current = current->next;
  }
  current->next = new;
  }
}

void  display(node** head)
{
    node* current = *head;
   if(*head == NULL)
    {
      printf("the stack is empty\n");
    }
    else
    {
     while(current->next != NULL)
     {
      printf("the data in stack is %d\n",current->data);
      current = current->next;
     }
     printf("the data in stack is %d\n",current->data);
    }
}

int main()
{
  node* head = NULL;
   for(int i = 10; i < 20 ; i++)
   {
     push(&head,i);
   }
 display(&head);
}