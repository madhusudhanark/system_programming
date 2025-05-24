//#include"My_header.h"
#include<stdio.h>
#include<stdlib.h>

int multiply(int a, int b) {
    return a * b;
}

/*
void  Insert_beginning(Node** head, int x)
{
    Node *temp = (Node*)malloc(sizeof(Node));
     if(!temp){
        printf("memory allocation failed\n");
        return;
     }
    temp->pre = NULL;
    temp->x = x;
    if(*head != NULL)
    {
       temp->next = *head;
       (*head)->pre = temp;
 
    }
    else
    {
        temp->next = NULL;
    }
    *head = temp;
}
*/