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
        printf("\n------------------------In Child Process---------------------------------\n");
        printf("Child process is executing a different program to display the sorted array in reverse order.\n");

 
    } else {
        // This is the parent process
        printf("\n--------------------In Parent Process------------------------------------\n");
        printf("Parent process is sorting the integers...\n");

        bubbleSort(arr, n);

        printf("Parent process sorting complete.\n");
        
        printf("Sorted %d integers:\n", n);
		for (int i = 0; i < n; i++) {
		    printf("%d", arr[i]);
		    printf(" ");
		}
		printf("\n");

        // Pass the sorted array as command-line arguments to the child program
        char *child_program = "./child.out";
        char *args[n + 2];  // Arguments for the child program (including program name and NULL)
        args[0] = child_program;
        for (int i = 0; i < n; i++) {
            args[i + 1] = malloc(10);  // Assuming each number can be represented by up to 10 characters
            snprintf(args[i + 1], 10, "%d", arr[i]);
        }
        args[n + 1] = NULL;

        // Execute the child program with execv
        execv(child_program, args);

        // If execv fails, print an error message
        perror("execv");
        exit(1);
    }

    return 0;
}
