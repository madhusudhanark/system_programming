#include<stdio.h>
#include "spi.h"

void push_end(int data)
{
    node *new = malloc(sizeof(node));
    new->data = data;
    node* current = head;

    if(head == NULL)
    {
        head = new;
        head->next = head; // assign back to head , circular linked list
    }
    else
    {
        while(current->next != head)
        {
            current = current->next;
        }
        current->next = new;
        new->next = head;

    }



}
// display function
void display()
{
   node* current = head;
   while(current->next !=head)
   {
     printf("node number %d\n",current->data);
     current = current->next;
   }


}