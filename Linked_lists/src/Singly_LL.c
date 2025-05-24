/* the  */
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>


typedef struct Node
{
  uint32_t x;
  uint32_t y;
  struct Node *next;
}Node1;

/*struct to test dennis retchie struct precedence cases*/

 struct Node2{
 int len;
 char *str;
};

/* create a new node*/
struct Node* CreateNode(uint32_t var){
  struct Node* New_Node = (struct Node*) malloc(sizeof(struct Node));
  if(New_Node == NULL){
    fprintf(stderr , " error while creating a new node\n" );
    return NULL;
  }
 New_Node->x = var;
 New_Node->next = NULL;
 return New_Node;
}


// to add new element at the end to linked list//
int  add_element_end(struct Node *head,uint32_t var)
{
  
  struct Node *current = head;

  while(current->next != NULL ) /* traverse to last node*/
  {

    current = current->next;
  }
  struct Node *next_node = (struct Node*)malloc(sizeof(struct Node));

  if(next_node == NULL){

    fprintf(stderr, " failed to create a node using malloc");
    return 1;
  };

  next_node->x = var;
  next_node->next = NULL;
  current->next = next_node;  //link current node to node created//
  return 0;
}

struct Node*  add_element_beg(struct Node *head,uint32_t var)
{
  struct Node *first_node = CreateNode(var);
  first_node->next = head;
  return first_node;

}



int main(){
struct Node *head = CreateNode(1);
struct Node *node1 = CreateNode(2);
struct Node *node2 = CreateNode(3);

struct Node2 *p = (struct Node2*) malloc(sizeof(struct Node2));
p->str = "test string in pointer strcuture";

printf("the string in dennis book example struct is :  %s\n",p->str);

char name[] = "madhu";
printf("name string before modifying the string dynamically : %s\n",name);
strcpy(name,"yadhunandan");
//char name[] = "priya";
printf("name string after modifying the string dynamically : %s\n",name);

head->x = 1;
head->next = node1;
node1->x = 2;
node1->next = node2;
node2->x = 3;
node2->next = NULL;

add_element_end(head ,2); /* add element to node at the end*/
head = add_element_beg(head,4); /* add element to node at the beginning*/

printf("after adding elements at the beginning %d",head->x);
return 0;
}

