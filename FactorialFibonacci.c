#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack definition for integers
typedef struct {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isStackFull(Stack *s) {
    return s->top == MAX - 1;
}

int isStackEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    if (isStackFull(s)) {
        printf("Stack is full. Cannot push %d.\n", value);
        return;
    }
    s->data[++(s->top)] = value;
}

int pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty. Cannot pop.\n");
        return -1;
    }
    return s->data[(s->top)--];
}

int factorialUsingStack(int n) {
    Stack s;
    initStack(&s);
    int result = 1;

    for (int i = n; i > 1; i--) {
        push(&s, i);
    }

    while (!isStackEmpty(&s)) {
        result *= pop(&s);
    }

    return result;
}

void fibonacciUsingStack(int n) {
    if (n <= 0) {
        printf("Invalid input. n must be greater than 0.\n");
        return;
    }

    Stack s;
    initStack(&s);
    int a = 0, b = 1, temp;

    push(&s, b); // First Fibonacci number
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
        push(&s, b);
    }

    printf("Fibonacci series up to %d terms:\n", n);
    while (!isStackEmpty(&s)) {
        printf("%d ", pop(&s));
    }
    printf("\n");
}

int main() {
    int choice, num;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Factorial of a given number\n");
        printf("2. Generation of Fibonacci series\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to find its factorial: ");
                scanf("%d", &num);
                if (num < 0) {
                    printf("Factorial is not defined for negative numbers.\n");
                } else {
                    printf("Factorial of %d is %d\n", num, factorialUsingStack(num));
                }
                break;
            case 2:
                printf("Enter the number of terms for Fibonacci series: ");
                scanf("%d", &num);
                fibonacciUsingStack(num);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
