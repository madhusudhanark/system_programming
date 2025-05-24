typdef struct Node {
 int x;
 struct Node *Prev;
 struct Node *next;

}Node;



void insert_beginning(Node **head , int x)
{
     Node *temp =(Node*)mallcoc(sizeof(Node));
     temp->next = *head;
     temp->prev = NULL;
     temp->x = x;
     *head = temp;
}

void insert_end(Node **head , int x)
{
     Node *current = (*head);
     Node *temp =(Node*)mallcoc(sizeof(Node));
     temp->next = NULL;
     temp->x = x;
     
     while(current->next != NULL)
     {
        current = current->next;
     }
     current->next = temp;
     temp->prev = current;
}

void insert_middle(Node **head , int x , int position)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    Node *temp = *head;


    if(position<= 1){

        insert_beninning();
        return;
    }

{


}
    while(temp && count < p-1)

    if(!temp || !temp->next )

    else
    {
       Newnode->next = temp->next;
       new_node->pre = temp;

         
    }

    {
       Node* temp = *head;
       *head = *head->next;


    }
 
     
    





}