#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the threaded binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int isThreaded; // Flag to indicate if the right pointer is threaded
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 0;
    return newNode;
}

// Function to insert a node into the threaded binary tree
struct Node* insert(struct Node* root, int data) {
    struct Node* newNode = createNode(data);

    if (root == NULL) {
        root = newNode;
        return root;
    }

    struct Node* current = root;
    struct Node* prev = NULL;

    while (current != NULL) {
        prev = current;
        if (data < current->data) {
            if (current->left == NULL) {
                current->left = newNode;
                newNode->right = current;
                newNode->isThreaded = 1;
                return root;
            } else {
                current = current->left;
            }
        } else {
            if (current->isThreaded == 1) {
                newNode->right = current->right;
                current->right = newNode;
                current->isThreaded = 0;
                newNode->isThreaded = 1;
                return root;
            } else {
                current = current->right;
            }
        }
    }

    if (data < prev->data) {
        prev->left = newNode;
        newNode->right = prev;
        newNode->isThreaded = 1;
    } else {
        prev->right = newNode;
    }

    return root;
}

// Function to traverse the threaded binary tree in preorder
void preorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* current = root;

    while (current != NULL) {
        printf("%d ", current->data);

        if (current->left != NULL) {
            current = current->left;
        } else {
            while (current != NULL && current->isThreaded) {
                current = current->right;
                if (current != NULL) {
                    printf("%d ", current->data);
                }
            }

            if (current != NULL && current->right != NULL) {
                current = current->right;
            } else {
                break;
            }
        }
    }
}

// Function to display the menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Insert Node\n");
    printf("2. Traverse in Preorder\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node* root = NULL;
    int choice, data;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Node inserted.\n");
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
