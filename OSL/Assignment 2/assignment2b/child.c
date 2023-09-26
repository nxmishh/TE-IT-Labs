#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Child process received the sorted array and is displaying it in reverse order:\n");

    // Skip the first argument (program name)
    for (int i = argc - 1; i > 0; i--) {
        // Convert the argument string to an integer and print it
        int num = atoi(argv[i]);
        printf("%d ", num);
    }
    printf("\n");

    return 0;
}

