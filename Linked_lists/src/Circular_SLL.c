#include<stdio.h>
#include<stdlib.h>
//#include<>


#ifndef MADHU_H
#define MADHU_H 2
#endif


typedef struct node
{
    int var;
    void*(*task_handler)(void*);
    struct node *next;
}node;

node* head = NULL;

void push(int data)
{
  node *new = (node*)malloc(sizeof(node));
  node* current;
  current =head;
  new->var = data;
  new->next = NULL;
  if(head == NULL)
  {
    head = new;
    (head)->next = NULL;
  }
  else{
    while(current->next != head && current->next != NULL)
    {
      current = current->next;
    }
    current->next = new;
    new->next = head;
    head = new;
  }
}

int disply(node *head)
{
    node* current = head;
    if(current == NULL)
    {

        printf("the head is empty\n");
        return 0;
    }
  while(current->next != head)
  {
    printf("the data is %d\n",current->var);
    current = current->next;
  }
  printf("the data is %d\n",current->var);
}


int main(){

    //node* head = NULL;
    for(int i = 10; i< 20 ;i++)
    {

      push(i);

    }
    disply(head);
    return 0;
}