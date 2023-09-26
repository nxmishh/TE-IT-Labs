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
    int arr_copy[n];

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        arr_copy[i] = arr[i];
    }

    // Create a child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (child_pid == 0) {
        // This is the child process
        printf("\n");
        printf("-----------------child process----------------------------");
        printf("\n");
        printf("Child process sorting the integers using bubble sort...\n");
        bubbleSort(arr, n);
        printf("Child process sorting complete.\n");
        printf("Sorted array (child process):\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("Child Process has exited!\n");
        exit(0);
    }
    else {
        // This is the parent process
        printf("\n");
        printf("-----------------parent process----------------------------");
        printf("\n");
        printf("Parent process sorting the integers using a different sorting algorithm...\n");


        for (int i = 0; i < n - 1; i++) {
            int min_index = i;
            for (int j = i + 1; j < n; j++) {
                if (arr_copy[j] < arr_copy[min_index]) {
                    min_index = j;
                }
            }
            // Swap the elements
            int temp = arr_copy[i];
            arr_copy[i] = arr_copy[min_index];
            arr_copy[min_index] = temp;

		}
        printf("Parent process sorting complete.\n");
        
        printf("Sorted array (parent process):\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr_copy[i]);
        }
        printf("\n");
		while(1){
			printf("Parent process is still running but child process has terminated!\n");
			sleep(1);
		}
        }

    return 0;
}


