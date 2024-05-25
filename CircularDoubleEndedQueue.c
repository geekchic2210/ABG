#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int front;
    int rear;
    int size;
} Deque;

void initDeque(Deque* dq) {
    dq->front = -1;
    dq->rear = -1;
    dq->size = 0;
}

int isFull(Deque* dq) {
    return dq->size == MAX;
}

int isEmpty(Deque* dq) {
    return dq->size == 0;
}

void insertFront(Deque* dq, int value) {
    if (isFull(dq)) {
        printf("Deque is full. Cannot insert %d at the front.\n", value);
        return;
    }
    if (dq->front == -1) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->front == 0) {
        dq->front = MAX - 1;
    } else {
        dq->front--;
    }
    dq->data[dq->front] = value;
    dq->size++;
}

void insertRear(Deque* dq, int value) {
    if (isFull(dq)) {
        printf("Deque is full. Cannot insert %d at the rear.\n", value);
        return;
    }
    if (dq->rear == -1) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->rear == MAX - 1) {
        dq->rear = 0;
    } else {
        dq->rear++;
    }
    dq->data[dq->rear] = value;
    dq->size++;
}

int deleteFront(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty. Cannot delete from the front.\n");
        return -1;
    }
    int value = dq->data[dq->front];
    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->front == MAX - 1) {
        dq->front = 0;
    } else {
        dq->front++;
    }
    dq->size--;
    return value;
}

int deleteRear(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty. Cannot delete from the rear.\n");
        return -1;
    }
    int value = dq->data[dq->rear];
    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->rear == 0) {
        dq->rear = MAX - 1;
    } else {
        dq->rear--;
    }
    dq->size--;
    return value;
}

void displayDeque(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty.\n");
        return;
    }
    printf("Deque elements: ");
    int i = dq->front;
    while (1) {
        printf("%d ", dq->data[i]);
        if (i == dq->rear) {
            break;
        }
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    Deque dq;
    initDeque(&dq);
    
    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at front\n");
        printf("2. Insert at rear\n");
        printf("3. Delete from front\n");
        printf("4. Delete from rear\n");
        printf("5. Display deque\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at front: ");
                scanf("%d", &value);
                insertFront(&dq, value);
                break;
            case 2:
                printf("Enter value to insert at rear: ");
                scanf("%d", &value);
                insertRear(&dq, value);
                break;
            case 3:
                value = deleteFront(&dq);
                if (value != -1) {
                    printf("Deleted %d from front\n", value);
                }
                break;
            case 4:
                value = deleteRear(&dq);
                if (value != -1) {
                    printf("Deleted %d from rear\n", value);
                }
                break;
            case 5:
                displayDeque(&dq);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
