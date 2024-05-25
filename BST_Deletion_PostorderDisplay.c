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

// Function to find the minimum value node in a subtree
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValueNode(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to display the tree in postorder
void displayTree(struct Node* root) {
    printf("Non-recursive Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Display Tree in Postorder\n");
    printf("4. Exit\n");
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
                if (root == NULL) {
                    printf("BST is empty. No node to delete.\n");
                    break;
                }
                printf("Enter data to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                printf("Node deleted.\n");
                break;
            case 3:
                if (root == NULL) {
                    printf("BST is empty. No tree to display.\n");
                    break;
                }
                displayTree(root);
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
