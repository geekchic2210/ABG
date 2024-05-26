#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];
int collision_count = 0;

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void insert(int key) {
    int hashIndex = hashFunction(key);
    int originalIndex = hashIndex;
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = key;
    newNode->next = NULL;

    if (hashTable[hashIndex] == NULL) {
        hashTable[hashIndex] = newNode;
    } else {
        collision_count++;
        if (hashTable[hashIndex]->data % TABLE_SIZE == originalIndex) {
            // Perform chaining
            Node* current = hashTable[hashIndex];
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        } else {
            // Replace the existing node and rehash the displaced node
            Node* displacedNode = hashTable[hashIndex];
            hashTable[hashIndex] = newNode;

            // Rehash the displaced node
            while (hashTable[hashIndex] != NULL) {
                hashIndex = (hashIndex + 1) % TABLE_SIZE;
            }
            hashTable[hashIndex] = displacedNode;

            // Maintain chaining for the displaced node
            while (displacedNode->next != NULL) {
                Node* nextNode = displacedNode->next;
                displacedNode->next = nextNode->next;
                hashIndex = hashFunction(nextNode->data);
                while (hashTable[hashIndex] != NULL) {
                    hashIndex = (hashIndex + 1) % TABLE_SIZE;
                }
                hashTable[hashIndex] = nextNode;
            }
        }
    }
}

void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* current = hashTable[i];
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void printMenu() {
    printf("\nHash Table Menu\n");
    printf("1. Insert a key\n");
    printf("2. Display hash table\n");
    printf("3. Show number of collisions\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice, key;
    
    // Initialize hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                display();
                break;
            case 3:
                printf("Number of collisions: %d\n", collision_count);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
