#include <stdio.h>

void findSwappedPair(int arr[], int n) {
    int x = -1, y = -1; // Variables to store the indices of the swapped elements

    // Traverse the array to find the first out-of-order pair
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            x = i;
            break;
        }
    }

    // If the first out-of-order pair is found, continue to find the second
    if (x != -1) {
        for (int i = x + 1; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                y = i + 1;
                break;
            }
        }
        
        // If no second out-of-order pair found, the pair must be adjacent
        if (y == -1) {
            y = x + 1;
        }

        // Print the swapped elements and their positions
        printf("Swapped elements are %d and %d at positions %d and %d\n", arr[x], arr[y], x, y);
    } else {
        printf("No swapped elements found.\n");
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    findSwappedPair(arr, n);

    return 0;
}
