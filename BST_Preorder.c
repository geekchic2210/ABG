#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the binary search tree
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

// Function to perform preorder traversal non-recursively
void preorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;

    push(stack, &top, root);

    while (top != -1) {
        struct Node* current = pop(stack, &top);
        printf("%d ", current->data);

        if (current->right != NULL) push(stack, &top, current->right);
        if (current->left != NULL) push(stack, &top, current->left);
    }
}

// Function to count total number of nodes non-recursively
int countTotalNodes(struct Node* root) {
    if (root == NULL) return 0;

    int count = 0;
    struct Node* stack[100];
    int top = -1;

    push(stack, &top, root);

    while (top != -1) {
        struct Node* current = pop(stack, &top);
        count++;

        if (current->right != NULL) push(stack, &top, current->right);
        if (current->left != NULL) push(stack, &top, current->left);
    }

    return count;
}

// Function to display leaf nodes non-recursively
void displayLeafNodes(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;

    push(stack, &top, root);

    while (top != -1) {
        struct Node* current = pop(stack, &top);

        if (current->right == NULL && current->left == NULL) printf("%d ", current->data);

        if (current->right != NULL) push(stack, &top, current->right);
        if (current->left != NULL) push(stack, &top, current->left);
    }
}

// Function to insert a node into the BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return createNode(data);

    struct Node* current = root;
    struct Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data <= current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (data <= parent->data)
        parent->left = createNode(data);
    else
        parent->right = createNode(data);

    return root;
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Insert\n");
    printf("2. Preorder Traversal\n");
    printf("3. Display total Number of Nodes\n");
    printf("4. Display Leaf nodes\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node* root = NULL;
    int choice, data;

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Data inserted.\n");
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Total Number of Nodes: %d\n", countTotalNodes(root));
                break;
            case 4:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
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

