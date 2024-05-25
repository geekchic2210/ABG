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

// Function to insert a node into the BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// Function to perform inorder traversal non-recursively
void inorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

// Function to create the mirror image of the tree without disturbing the original tree
struct Node* createMirrorImage(struct Node* root) {
    if (root == NULL) return NULL;

    struct Node* mirrorRoot = createNode(root->data);
    mirrorRoot->left = createMirrorImage(root->right);
    mirrorRoot->right = createMirrorImage(root->left);

    return mirrorRoot;
}

// Function to create the mirror image of the tree and overwrite the original tree
void createAndOverwriteMirrorImage(struct Node* root) {
    if (root == NULL) return;

    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    createAndOverwriteMirrorImage(root->left);
    createAndOverwriteMirrorImage(root->right);
}

// Function to calculate the height of the tree using non-recursion
int heightOfTree(struct Node* root) {
    if (root == NULL) return 0;

    struct Node* stack[100];
    int top = -1;
    int maxHeight = 0;
    int currentHeight = 0;
    struct Node* current = root;
    struct Node* prev = NULL;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
            currentHeight++;
        }

        current = stack[top];

        if (current->right == NULL || prev == current->right) {
            if (currentHeight > maxHeight) {
                maxHeight = currentHeight;
            }
            currentHeight--;
            top--;
            prev = current;
            current = NULL;
        } else {
            current = current->right;
            prev = NULL;
        }
    }

    return maxHeight;
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Insert\n");
    printf("2. Display Tree\n");
    printf("3. Display Mirror Image without Disturbing Original Tree\n");
    printf("4. Display Mirror Image with Overwriting Original Tree\n");
    printf("5. Display Height of Tree\n");
    printf("6. Exit\n");
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
                printf("Original Tree: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Mirror Image without Disturbing Original Tree: ");
                inorderTraversal(createMirrorImage(root));
                printf("\n");
                break;
            case 4:
                createAndOverwriteMirrorImage(root);
                printf("Mirror Image with Overwriting Original Tree: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Height of the Tree: %d\n", heightOfTree(root));
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
