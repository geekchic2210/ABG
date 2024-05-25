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

// Function to perform inorder traversal non-recursively
void inorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            push(stack, &top, current);
            current = current->left;
        }

        current = pop(stack, &top);
        printf("%d ", current->data);
        current = current->right;
    }
}

// Function to display the number of leaf nodes non-recursively
int countLeafNodes(struct Node* root) {
    if (root == NULL) return 0;

    int count = 0;
    struct Node* stack[100];
    int top = -1;

    do {
        while (root != NULL) {
            push(stack, &top, root);
            root = root->left;
        }

        while (root == NULL && top != -1) {
            struct Node* peekNode = stack[top--];
            if (peekNode->left == NULL && peekNode->right == NULL) {
                count++;
            }
            root = peekNode->right;
        }
    } while (top != -1);

    return count;
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
    printf("2. Inorder Traversal\n");
    printf("3. Display Number of Leaf Nodes\n");
    printf("4. Create Mirror Image\n");
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
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));
                break;
            case 4:
                mirrorImage(root);
                printf("Mirror Image of the tree created.\n");
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
