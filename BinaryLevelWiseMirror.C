#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to perform level-wise display (Breadth-First Traversal) non-recursively
void levelWiseDisplay(struct Node* root) {
    if (root == NULL) return;

    struct Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front < rear) {
        struct Node* node = queue[++front];

        printf("%d ", node->data);

        if (node->left) queue[++rear] = node->left;
        if (node->right) queue[++rear] = node->right;
    }
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

// Function to find the height of the tree non-recursively
int findHeight(struct Node* root) {
    if (root == NULL) return 0;

    struct Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;
    int height = 0;

    while (1) {
        int nodeCount = rear - front;
        if (nodeCount == 0) return height;

        height++;
        while (nodeCount > 0) {
            struct Node* node = queue[++front];

            if (node->left) queue[++rear] = node->left;
            if (node->right) queue[++rear] = node->right;

            nodeCount--;
        }
    }
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Level-wise Display\n");
    printf("2. Mirror Image\n");
    printf("3. Display Height of the Tree\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    // Creating a sample binary tree
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    int choice;
    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Level-wise Display: ");
                levelWiseDisplay(root);
                printf("\n");
                break;
            case 2:
                mirrorImage(root);
                printf("Mirror image of the tree created.\n");
                printf("Level-wise Display of Mirror Image: ");
                levelWiseDisplay(root);
                printf("\n");
                break;
            case 3: {
                int height = findHeight(root);
                printf("Height of the Tree: %d\n", height);
                break;
            }
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
