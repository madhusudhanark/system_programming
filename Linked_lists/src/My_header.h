#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
  int x;
  struct Node* pre;
  struct Node* next;
}Node;

int multiply(int a, int b);
void  Insert_beginning(Node** head, int x);