#include <stdio.h>
#include <stdlib.h>

// Node structure for polynomial linked list
typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the end of the linked list
void insertEnd(Node** head, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to display a polynomial
void displayPoly(Node* head) {
    if (head == NULL) {
        printf("0");
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        printf("%dx^%d", temp->coeff, temp->exp);
        temp = temp->next;
        if (temp != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to add two polynomials
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    Node* p1 = poly1;
    Node* p2 = poly2;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            insertEnd(&result, p1->coeff + p2->coeff, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            insertEnd(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            insertEnd(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    // Insert remaining terms of the first polynomial
    while (p1 != NULL) {
        insertEnd(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    // Insert remaining terms of the second polynomial
    while (p2 != NULL) {
        insertEnd(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;

    // Create first polynomial: 3x^3 + 5x^2 + 6
    insertEnd(&poly1, 3, 3);
    insertEnd(&poly1, 5, 2);
    insertEnd(&poly1, 6, 0);

    // Create second polynomial: 4x^3 + 2x + 4
    insertEnd(&poly2, 4, 3);
    insertEnd(&poly2, 2, 1);
    insertEnd(&poly2, 4, 0);

    printf("First Polynomial: ");
    displayPoly(poly1);

    printf("Second Polynomial: ");
    displayPoly(poly2);

    Node* result = addPolynomials(poly1, poly2);

    printf("Resultant Polynomial after addition: ");
    displayPoly(result);

    return 0;
}
