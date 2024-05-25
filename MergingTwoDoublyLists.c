#include <stdio.h>
#include <stdlib.h>

// Structure for a doubly linked list node
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Function to display the doubly linked list
void displayList(Node* head) {
    Node* temp = head;
    printf("Doubly Linked List: ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to merge two sorted doubly linked lists
Node* mergeSortedLists(Node* list1, Node* list2) {
    Node* mergedList = NULL;
    Node* tail = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            if (mergedList == NULL) {
                mergedList = list1;
                tail = list1;
            } else {
                tail->next = list1;
                list1->prev = tail;
                tail = list1;
            }
            list1 = list1->next;
        } else {
            if (mergedList == NULL) {
                mergedList = list2;
                tail = list2;
            } else {
                tail->next = list2;
                list2->prev = tail;
                tail = list2;
            }
            list2 = list2->next;
        }
    }

    if (list1 != NULL) {
        tail->next = list1;
        list1->prev = tail;
    }
    if (list2 != NULL) {
        tail->next = list2;
        list2->prev = tail;
    }

    return mergedList;
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert into first sorted list\n");
        printf("2. Insert into second sorted list\n");
        printf("3. Merge and display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        // Clear input buffer
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Enter data to insert into first sorted list: ");
                scanf("%d", &data);
                insertAtEnd(&list1, data);
                break;
            case 2:
                printf("Enter data to insert into second sorted list: ");
                scanf("%d", &data);
                insertAtEnd(&list2, data);
                break;
            case 3:
                if (list1 == NULL || list2 == NULL) {
                    printf("Both lists must have elements to merge\n");
                } else {
                    printf("First sorted list: ");
                    displayList(list1);
                    printf("Second sorted list: ");
                    displayList(list2);
                    Node* mergedList = mergeSortedLists(list1, list2);
                    printf("Merged sorted list: ");
                    displayList(mergedList);
                }
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
