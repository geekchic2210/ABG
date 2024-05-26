#include <stdio.h>
#include <string.h>

typedef struct {
    char student_name[50];
    int student_roll_no;
    int total_marks;
} Student;

int swap_count = 0;

void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
    swap_count++;
}

void heapify(Student arr[], int n, int i) {
    int largest = i;  // Initialize largest as root
    int left = 2 * i + 1;  // left = 2*i + 1
    int right = 2 * i + 2;  // right = 2*i + 2

    // If left child is larger than root
    if (left < n && arr[left].student_roll_no > arr[largest].student_roll_no)
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right].student_roll_no > arr[largest].student_roll_no)
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void heapSort(Student arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void printStudents(Student arr[], int n) {
    printf("\nStudent Details:\n");
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Roll No: %d, Total Marks: %d\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
    }
}

void printMenu() {
    printf("\nHeap Sort on Student Records\n");
    printf("1. Enter student records\n");
    printf("2. Perform Heap Sort\n");
    printf("3. Display student records\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice, n;
    Student students[100];

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of students: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("Enter details for student %d:\n", i + 1);
                    printf("Name: ");
                    scanf("%s", students[i].student_name);
                    printf("Roll No: ");
                    scanf("%d", &students[i].student_roll_no);
                    printf("Total Marks: ");
                    scanf("%d", &students[i].total_marks);
                }
                break;
            case 2:
                swap_count = 0;  // Reset swap count
                heapSort(students, n);
                printf("Heap Sort performed with %d swaps.\n", swap_count);
                break;
            case 3:
                printStudents(students, n);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
