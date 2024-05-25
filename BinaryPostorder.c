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

// Function to perform non-recursive postorder traversal
void postorderTraversal(struct Node* root) {
    if (root == NULL) return;
    
    struct Node* stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;
    
    while (top1 >= 0) {
        struct Node* node = stack1[top1--];
        stack2[++top2] = node;
        
        if (node->left) stack1[++top1] = node->left;
        if (node->right) stack1[++top1] = node->right;
    }
    
    while (top2 >= 0) {
        struct Node* node = stack2[top2--];
        printf("%d ", node->data);
    }
}

// Function to display leaf nodes non-recursively
void displayLeafNodes(struct Node* root) {
    if (root == NULL) return;
    
    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;
    
    while (top >= 0) {
        struct Node* node = stack[top--];
        
        if (node->left == NULL && node->right == NULL) {
            printf("%d ", node->data);
        }
        
        if (node->right) stack[++top] = node->right;
        if (node->left) stack[++top] = node->left;
    }
}

// Function to count total number of leaf nodes non-recursively
int countLeafNodes(struct Node* root) {
    if (root == NULL) return 0;
    
    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;
    int leafCount = 0;
    
    while (top >= 0) {
        struct Node* node = stack[top--];
        
        if (node->left == NULL && node->right == NULL) {
            leafCount++;
        }
        
        if (node->right) stack[++top] = node->right;
        if (node->left) stack[++top] = node->left;
    }
    
    return leafCount;
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
    printf("1. Postorder Traversal\n");
    printf("2. Display Leaf Nodes\n");
    printf("3. Count Total Number of Leaf Nodes\n");
    printf("4. Display Height of the Tree\n");
    printf("5. Exit\n");
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
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 2:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                printf("\n");
                break;
            case 3: {
                int leafCount = countLeafNodes(root);
                printf("Total Number of Leaf Nodes: %d\n", leafCount);
                break;
            }
            case 4: {
                int height = findHeight(root);
                printf("Height of the Tree: %d\n", height);
                break;
            }
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
