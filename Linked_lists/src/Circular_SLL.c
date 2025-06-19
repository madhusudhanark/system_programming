#include<stdio.h>
#include<stdlib.h>
//#include<>


#ifndef MADHU_H
#define MADHU_H 2
#endif


typedef struct node
{
    int var;
    struct node *next;
}node;

void push(node **head,int data)
{
  node* current;
  node *new;
  current =*head;
  new = (node*)malloc(sizeof(node));
  new->var = data;
  if(*head == NULL)
  {
    *head = new;
    (*head)->next = NULL;
  }
  else{
    while(current->next != NULL)
    {
      current = current->next;
      
    }
    current->next = new;
    current->next->next = *head;
  }
    
}

void* disply(node* head)
{
    node* current = head;
    if(current == NULL)
    {

        printf("the head is empty\n");
        return NULL;
    }
  while(current->next != head)
  {
    printf("the data is %d",current->var);
    current = current->next;
  }
}


int main(){

    node* head = NULL;
    for(int i = 10; i< 20 ;i++)
    {

      push(&head,i);

    }
    disply(head);
    return 0;
}