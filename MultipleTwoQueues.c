#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define NUM_QUEUES 2

typedef struct {
    int data[MAX];
    int front[NUM_QUEUES];
    int rear[NUM_QUEUES];
} MultiQueue;

void initMultiQueue(MultiQueue* mq) {
    for (int i = 0; i < NUM_QUEUES; i++) {
        mq->front[i] = -1;
        mq->rear[i] = -1;
    }
}

int isFull(MultiQueue* mq, int qnum) {
    return (mq->rear[qnum] + 1) % MAX == mq->front[qnum];
}

int isEmpty(MultiQueue* mq, int qnum) {
    return mq->front[qnum] == -1;
}

void addq(MultiQueue* mq, int qnum, int value) {
    if (isFull(mq, qnum)) {
        printf("Queue %d is full. Cannot add %d.\n", qnum + 1, value);
        return;
    }
    if (mq->front[qnum] == -1) {
        mq->front[qnum] = 0;
    }
    mq->rear[qnum] = (mq->rear[qnum] + 1) % MAX;
    mq->data[mq->rear[qnum]] = value;
}

int delq(MultiQueue* mq, int qnum) {
    if (isEmpty(mq, qnum)) {
        printf("Queue %d is empty. Cannot delete.\n", qnum + 1);
        return -1;
    }
    int value = mq->data[mq->front[qnum]];
    if (mq->front[qnum] == mq->rear[qnum]) {
        mq->front[qnum] = -1;
        mq->rear[qnum] = -1;
    } else {
        mq->front[qnum] = (mq->front[qnum] + 1) % MAX;
    }
    return value;
}

void displayQueue(MultiQueue* mq, int qnum) {
    if (isEmpty(mq, qnum)) {
        printf("Queue %d is empty.\n", qnum + 1);
        return;
    }
    printf("Queue %d elements: ", qnum + 1);
    int i = mq->front[qnum];
    while (1) {
        printf("%d ", mq->data[i]);
        if (i == mq->rear[qnum]) {
            break;
        }
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    MultiQueue mq;
    initMultiQueue(&mq);
    
    int choice, qnum, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add to Queue\n");
        printf("2. Delete from Queue\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter queue number (1 or 2): ");
                scanf("%d", &qnum);
                if (qnum < 1 || qnum > 2) {
                    printf("Invalid queue number. Please try again.\n");
                    break;
                }
                printf("Enter value to add: ");
                scanf("%d", &value);
                addq(&mq, qnum - 1, value);
                break;
            case 2:
                printf("Enter queue number (1 or 2): ");
                scanf("%d", &qnum);
                if (qnum < 1 || qnum > 2) {
                    printf("Invalid queue number. Please try again.\n");
                    break;
                }
                value = delq(&mq, qnum - 1);
                if (value != -1) {
                    printf("Deleted %d from Queue %d\n", value, qnum);
                }
                break;
            case 3:
                printf("Enter queue number (1 or 2) to display: ");
                scanf("%d", &qnum);
                if (qnum < 1 || qnum > 2) {
                    printf("Invalid queue number. Please try again.\n");
                    break;
                }
                displayQueue(&mq, qnum - 1);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
