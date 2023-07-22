#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int x;
    struct Node *next;
};

int addElements(int number, struct Node *head)
{
    struct Node *current;
    current = head;
    for (int i = 0; i < number; i++)
    {
        current = malloc(sizeof(struct Node));
        if (i == number - 1)
        {
            current->next = NULL;
        }
        else
        {

            current = current->next;
        }
    }
}

int main()
{
    struct Node *head;
    struct Node *curr;

    addElements(10, head);

    for (curr = head; curr != NULL; curr = curr->next)
    {
        printf("%p has %d\n", curr, curr->x);
    }
}