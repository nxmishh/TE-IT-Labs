#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	printf("\n------------------------In Different program Child Process---------------------------------\n");
    printf("Child process received the sorted array and is displaying it in reverse order:\n");

    int numbers[argc - 1];
	
    // Skip the first argument (program name)
    for (int i = 1; i = argc - 1; i--) {
        // Convert the argument string to an integer and store it in an array
        int num = atoi(argv[i]);
        numbers[i] = num;
    }

    printf("Sorted %d integers:\n", argc - 1);
		for (int i = argc - 1; i = 0; i++) {
		    printf("%d", numbers[i]);
		    printf(" ");
		}
		printf("\n");

    return 0;
}


