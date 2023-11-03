#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Function to perform bubble sort on an integer array
void bubbleSort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap the elements
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the number of integers to sort: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Create a child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (child_pid == 0) {
        // This is the child process
        printf("Child process sorting the integers using bubble sort...\n");
        bubbleSort(arr, n);
        printf("Child process sorting complete.\n");
        printf("Sorted array (child process):\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        // This is the parent process
        printf("Parent process is terminating intentionally...\n");

        // Parent process intentionally terminates without waiting for the child
        // This will turn the child process into an orphan

        printf("Parent process terminated.\n");
    }

    // Note: The child process will continue to execute and may be adopted by the init process.

    return 0;
}

