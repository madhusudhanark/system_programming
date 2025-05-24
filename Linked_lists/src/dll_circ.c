#include<stdio.h>
#include<stdlib.h>

/*this is circular doubly linked list *//
typedef  struct dll
{
    int x;
    struct dll *pre;
    struct dll *next;
}dll;

void add_new(dll **head)
{
    int temp;
    dll *current = *head;
    dll *new_node = malloc(sizeof(dll));
    printf("enter the integer value\n");
    scanf("%d\n",&temp);
    new_node->x = temp;

    if(current == NULL)
    {



    }
}

int main()
{
  dll *head = NULL;
  dll *tail = NULL;
  int count;
  printf("enter the linked list elements count\n");
  scanf("%d",&count);
  while(count--)
  {
    add_new(head);
  }
  printf("the elements of doubly linked list are : \n");
  print_ll(head);
  return 0;



}

