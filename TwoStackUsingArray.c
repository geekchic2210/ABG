#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int top1;
    int top2;
} TwoStacks;

void initialize(TwoStacks *stacks) {
    stacks->top1 = -1;
    stacks->top2 = MAX;
}

int isStackFull(TwoStacks *stacks) {
    return stacks->top1 + 1 == stacks->top2;
}

int isStackEmpty(TwoStacks *stacks, int stackNumber) {
    if (stackNumber == 1) {
        return stacks->top1 == -1;
    } else if (stackNumber == 2) {
        return stacks->top2 == MAX;
    }
    return 0;
}

void push(TwoStacks *stacks, int stackNumber, int value) {
    if (isStackFull(stacks)) {
        printf("Stack is full. Cannot push %d.\n", value);
        return;
    }

    if (stackNumber == 1) {
        stacks->arr[++(stacks->top1)] = value;
    } else if (stackNumber == 2) {
        stacks->arr[--(stacks->top2)] = value;
    }
}

int pop(TwoStacks *stacks, int stackNumber) {
    if (stackNumber == 1) {
        if (isStackEmpty(stacks, 1)) {
            printf("Stack 1 is empty. Cannot pop.\n");
            return -1;
        }
        return stacks->arr[(stacks->top1)--];
    } else if (stackNumber == 2) {
        if (isStackEmpty(stacks, 2)) {
            printf("Stack 2 is empty. Cannot pop.\n");
            return -1;
        }
        return stacks->arr[(stacks->top2)++];
    }
    return -1;
}

void displayStack(TwoStacks *stacks, int stackNumber) {
    if (stackNumber == 1) {
        if (isStackEmpty(stacks, 1)) {
            printf("Stack 1 is empty.\n");
            return;
        }
        printf("Stack 1: ");
        for (int i = 0; i <= stacks->top1; i++) {
            printf("%d ", stacks->arr[i]);
        }
        printf("\n");
    } else if (stackNumber == 2) {
        if (isStackEmpty(stacks, 2)) {
            printf("Stack 2 is empty.\n");
            return;
        }
        printf("Stack 2: ");
        for (int i = MAX - 1; i >= stacks->top2; i--) {
            printf("%d ", stacks->arr[i]);
        }
        printf("\n");
    }
}

int main() {
    TwoStacks stacks;
    initialize(&stacks);

    int choice, stackNumber, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. StackFull\n");
        printf("4. StackEmpty\n");
        printf("5. Display Stack\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stackNumber);
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(&stacks, stackNumber, value);
                break;
            case 2:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stackNumber);
                value = pop(&stacks, stackNumber);
                if (value != -1) {
                    printf("Popped value: %d\n", value);
                }
                break;
            case 3:
                if (isStackFull(&stacks)) {
                    printf("Stack is full.\n");
                } else {
                    printf("Stack is not full.\n");
                }
                break;
            case 4:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stackNumber);
                if (isStackEmpty(&stacks, stackNumber)) {
                    printf("Stack %d is empty.\n", stackNumber);
                } else {
                    printf("Stack %d is not empty.\n", stackNumber);
                }
                break;
            case 5:
                printf("Enter stack number (1 or 2) to display: ");
                scanf("%d", &stackNumber);
                displayStack(&stacks, stackNumber);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
