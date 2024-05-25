#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the binary tree
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

// Function to push a node onto the stack
void push(struct Node* stack[], int *top, struct Node* node) {
    stack[++(*top)] = node;
}

// Function to pop a node from the stack
struct Node* pop(struct Node* stack[], int *top) {
    return stack[(*top)--];
}

// Function to perform postorder traversal non-recursively
void postorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    struct Node* prev = NULL;

    do {
        while (root != NULL) {
            push(stack, &top, root);
            root = root->left;
        }

        while (root == NULL && top != -1) {
            struct Node* peekNode = stack[top];
            if (peekNode->right == NULL || peekNode->right == prev) {
                printf("%d ", peekNode->data);
                prev = peekNode;
                pop(stack, &top);
            } else {
                root = peekNode->right;
            }
        }
    } while (top != -1);
}

// Function to display leaf nodes non-recursively
void displayLeafNodes(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;

    do {
        while (root != NULL) {
            push(stack, &top, root);
            root = root->left;
        }

        while (root == NULL && top != -1) {
            struct Node* peekNode = stack[top];
            if (peekNode->left == NULL && peekNode->right == NULL) {
                printf("%d ", peekNode->data);
            }
            pop(stack, &top);
            root = peekNode->right;
        }
    } while (top != -1);
}

// Function to create the mirror image of the tree non-recursively
void mirrorImage(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;

    do {
        while (root != NULL) {
            push(stack, &top, root);
            struct Node* temp = root->left;
            root->left = root->right;
            root->right = temp;
            root = root->left;
        }

        while (root == NULL && top != -1) {
            root = stack[top--];
            root = root->right;
        }
    } while (top != -1);
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Postorder Traversal\n");
    printf("2. Display Leaf Nodes\n");
    printf("3. Create Mirror Image\n");
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
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 2:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                printf("\n");
                break;
            case 3:
                mirrorImage(root);
                printf("Mirror Image of the tree created.\n");
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
