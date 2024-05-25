#include <stdio.h>
#include <stdlib.h>

// Structure for an employee record
struct Employee {
    int empId;
    char name[50];
    // You can add more fields as needed
    struct Employee* left;
    struct Employee* right;
};

// Function to create a new employee node
struct Employee* createEmployeeNode(int empId, const char* name) {
    struct Employee* newNode = (struct Employee*)malloc(sizeof(struct Employee));
    newNode->empId = empId;
    strcpy(newNode->name, name);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert an employee record into the BST
struct Employee* insertEmployee(struct Employee* root, int empId, const char* name) {
    if (root == NULL)
        return createEmployeeNode(empId, name);

    if (empId < root->empId)
        root->left = insertEmployee(root->left, empId, name);
    else if (empId > root->empId)
        root->right = insertEmployee(root->right, empId, name);

    return root;
}

// Function to search for an employee record by employee ID
struct Employee* searchEmployee(struct Employee* root, int empId) {
    while (root != NULL) {
        if (empId < root->empId)
            root = root->left;
        else if (empId > root->empId)
            root = root->right;
        else
            return root;
    }
    return NULL; // Employee not found
}

// Function to perform inorder traversal to sort the employee records by employee ID
void inorderTraversal(struct Employee* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Employee ID: %d, Name: %s\n", root->empId, root->name);
        inorderTraversal(root->right);
    }
}

// Function to display the menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Add Employee Record\n");
    printf("2. Search Employee Record\n");
    printf("3. Display Employee Records (Sorted by Employee ID)\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Employee* root = NULL;
    int choice, empId;
    char name[50];

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &empId);
                printf("Enter Employee Name: ");
                scanf("%s", name);
                root = insertEmployee(root, empId, name);
                printf("Employee Record Added.\n");
                break;
            case 2:
                printf("Enter Employee ID to search: ");
                scanf("%d", &empId);
                struct Employee* employee = searchEmployee(root, empId);
                if (employee != NULL)
                    printf("Employee Found - ID: %d, Name: %s\n", employee->empId, employee->name);
                else
                    printf("Employee Not Found.\n");
                break;
            case 3:
                printf("Employee Records Sorted by Employee ID:\n");
                inorderTraversal(root);
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
