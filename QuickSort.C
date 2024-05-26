#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char employee_name[50];
    int emp_no;
    float emp_salary;
} Employee;

int swap_count = 0;

void swap(Employee *a, Employee *b) {
    Employee temp = *a;
    *a = *b;
    *b = temp;
    swap_count++;
}

int partition(Employee arr[], int low, int high) {
    int pivot = arr[high].emp_no;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].emp_no < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(Employee arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printEmployees(Employee arr[], int n) {
    printf("\nEmployee Details:\n");
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Emp No: %d, Salary: %.2f\n", arr[i].employee_name, arr[i].emp_no, arr[i].emp_salary);
    }
}

void printMenu() {
    printf("\nQuick Sort on Employee Records\n");
    printf("1. Enter employee records\n");
    printf("2. Perform Quick Sort\n");
    printf("3. Display employee records\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice, n;
    Employee employees[100];

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of employees: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("Enter details for employee %d:\n", i + 1);
                    printf("Name: ");
                    scanf("%s", employees[i].employee_name);
                    printf("Emp No: ");
                    scanf("%d", &employees[i].emp_no);
                    printf("Salary: ");
                    scanf("%f", &employees[i].emp_salary);
                }
                break;
            case 2:
                swap_count = 0;  // Reset swap count
                quickSort(employees, 0, n - 1);
                printf("Quick Sort performed with %d swaps.\n", swap_count);
                break;
            case 3:
                printEmployees(employees, n);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
