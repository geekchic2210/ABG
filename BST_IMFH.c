#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the BST
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a key into the BST
struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return createNode(key);
    
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    
    return node;
}

// Function to find a key in the BST
struct Node* find(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return find(root->left, key);

    return find(root->right, key);
}

// Function to create the mirror image of the tree non-recursively
void mirrorImage(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        struct Node* node = stack[top--];

        // Swap the left and right children
        struct Node* temp = node->left;
        node->left = node->right;
        node->right = temp;

        if (node->left) stack[++top] = node->left;
        if (node->right) stack[++top] = node->right;
    }
}

// Function to print the tree in-order
void printTree(struct Node* node) {
    if (node == NULL) return;

    printTree(node->left);
    printf("%d ", node->key);
    printTree(node->right);
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Insert\n");
    printf("2. Mirror Image\n");
    printf("3. Find\n");
    printf("4. Print Tree\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                printf("Key inserted.\n");
                break;
            case 2:
                mirrorImage(root);
                printf("Mirror image of the tree created.\n");
                break;
            case 3:
                printf("Enter key to find: ");
                scanf("%d", &key);
                struct Node* found = find(root, key);
                if (found != NULL)
                    printf("Key %d found in the BST.\n", key);
                else
                    printf("Key %d not found in the BST.\n", key);
                break;
            case 4:
                printf("Tree in-order: ");
                printTree(root);
                printf("\n");
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
