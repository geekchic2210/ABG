#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
    int leftThread, rightThread;
} Node;

Node* insert(Node* root, int data) {
    Node* ptr = root;
    Node* parent = NULL;

    while (ptr != NULL) {
        if (data == ptr->data) {
            printf("Duplicate data is not allowed in BST\n");
            return root;
        }
        parent = ptr;
        if (data < ptr->data) {
            if (ptr->leftThread == 0)
                ptr = ptr->left;
            else
                break;
        } else {
            if (ptr->rightThread == 0)
                ptr = ptr->right;
            else
                break;
        }
    }

    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->data = data;
    tmp->leftThread = 1;
    tmp->rightThread = 1;

    if (parent == NULL) {
        root = tmp;
        tmp->left = NULL;
        tmp->right = NULL;
    } else if (data < parent->data) {
        tmp->left = parent->left;
        tmp->right = parent;
        parent->leftThread = 0;
        parent->left = tmp;
    } else {
        tmp->left = parent;
        tmp->right = parent->right;
        parent->rightThread = 0;
        parent->right = tmp;
    }

    return root;
}

Node* leftMost(Node* node) {
    while (node != NULL && node->leftThread == 0)
        node = node->left;
    return node;
}

void inorderTraversal(Node* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }

    Node* cur = leftMost(root);
    while (cur != NULL) {
        printf("%d ", cur->data);
        if (cur->rightThread)
            cur = cur->right;
        else
            cur = leftMost(cur->right);
    }
    printf("\n");
}

void displayMenu() {
    printf("Menu:\n");
    printf("1. Insert\n");
    printf("2. Inorder Traversal\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Node* root = NULL;
    int choice, data;

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice, please try again\n");
        }
    }
    return 0;
}
