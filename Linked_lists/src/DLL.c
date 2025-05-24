#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function prototypes
Node* createNode(int data);
void insertAtBeginning(Node** head, int data);
void insertAtEnd(Node** head, int data);
void insertInMiddle(Node** head, int data, int position);
void deleteNode(Node** head, int key);
void deleteAtBeginning(Node** head);
void deleteAtEnd(Node** head);
void traverseForward(Node* head);
void traverseBackward(Node* tail);
void freeList(Node** head);

int main() {
    Node* head = NULL; // Initialize the list as empty

    // Insert some nodes
    insertAtBeginning(&head, 10);
    insertAtBeginning(&head, 20);
    insertAtEnd(&head, 5);
    insertAtEnd(&head, 15);
    insertInMiddle(&head, 25, 3);

    printf("List after insertions (forward): ");
    traverseForward(head);

    // Delete some nodes
    deleteAtBeginning(&head);
    deleteAtEnd(&head);
    deleteNode(&head, 25);

    printf("\nList after deletions (forward): ");
    traverseForward(head);

    // Free the entire list
    freeList(&head);

    // Check if the list is freed
    if (!head) {
        printf("\nList has been freed successfully.\n");
    }

    return 0;
}

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Insert a node at the beginning of the list
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Insert a node at the end of the list
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Insert a node in the middle at a specific position
void insertInMiddle(Node** head, int data, int position) {
    if (position <= 1) {
        insertAtBeginning(head, data);
        return;
    }

    Node* newNode = createNode(data);
    Node* temp = *head;
    int count = 1;

    // Traverse to the desired position
    while (temp && count < position - 1) {
        temp = temp->next;
        count++;
    }

    if (!temp || !temp->next) {
        insertAtEnd(head, data);
    } else {
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next) {
            temp->next->prev = newNode;
        }
        temp->next = newNode;
    }
}

// Delete a node with a specific key
void deleteNode(Node** head, int key) {
    if (*head == NULL) {
        printf("\nList is empty\n");
        return;
    }
    Node* temp = *head;

    // Search for the node to delete
    while (temp && temp->data != key) {
        temp = temp->next;
    }

    if (!temp) {
        printf("\nKey %d not found\n", key);
        return;
    }

    // Adjust pointers
    if (temp->prev) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next; // Update head if the node to delete is the first node
    }

    if (temp->next) {
        temp->next->prev = temp->prev;
    }

    free(temp);
}

// Delete a node from the beginning of the list
void deleteAtBeginning(Node** head) {
    if (*head == NULL) {
        printf("\nList is empty\n");
        return;
    }

    Node* temp = *head;
    *head = temp->next;

    if (*head) {
        (*head)->prev = NULL;
    }

    free(temp);
}

// Delete a node from the end of the list
void deleteAtEnd(Node** head) {
    if (*head == NULL) {
        printf("\nList is empty\n");
        return;
    }

    Node* temp = *head;

    while (temp->next) {
        temp = temp->next;
    }

    if (temp->prev) {
        temp->prev->next = NULL;
    } else {
        *head = NULL; // If the list has only one node
    }

    free(temp);
}

// Traverse the list forward
void traverseForward(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

// Traverse the list backward
void traverseBackward(Node* tail) {
    Node* temp = tail;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
}

// Free the entire list
void freeList(Node** head) {
    Node* temp = *head;
    while (temp) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL; // Set head to NULL to indicate the list is empty
}
