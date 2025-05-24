#include<stdio.h>
#include<stdlib.h>

struct circ_LL
{
    int x;
    struct circ_LL *next;
};

void add_node_end(int x, struct circ_LL *head)
{
    struct circ_LL *current;
    struct circ_LL *new = malloc(sizeof(struct circ_LL));
    current = head;
    if(head == NULL)
    {
        printf("empty");
        exit;
    }
    while(current->next !=  head )
    {
        current = current->next;
    }
    new->x = x;
    new->next = head;
    current->next = new;
    
}


int main(){
    struct circ_LL *head = malloc(sizeof (struct circ_LL));
    struct circ_LL *n1 = malloc(sizeof (struct circ_LL));
    struct circ_LL *n2 = malloc(sizeof (struct circ_LL));
    struct circ_LL *n3 = malloc(sizeof (struct circ_LL));
    head->x = 1;
    head->next = n1;
    n1->x = 2;
    n1->next = n2;
    n2->x = 3;
    n2->next = n3;
    n3->x = 4;
    n3->next = head;
    add_node_end(4,head);
    return 0;
}