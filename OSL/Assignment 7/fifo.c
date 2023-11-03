#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BUF_SIZE 1024

int main() {
    int pipe1[2];  // Pipe for sending data from process 1 to process 2
    int pipe2[2];  // Pipe for sending data from process 2 to process 1
    pid_t child_pid;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();  // Create a child process

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // This is the child process (Process 2)

        close(pipe1[1]);  // Close write end of pipe1
        close(pipe2[0]);  // Close read end of pipe2

        FILE *output_file = fopen("output.txt", "w");
        if (output_file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        char buffer[MAX_BUF_SIZE];
        int char_count;

        while (1) {
            // Read data from pipe1 (sent by Process 1)
            ssize_t bytes_read = read(pipe1[0], buffer, MAX_BUF_SIZE);
            if (bytes_read <= 0) {
                break;  // End of input
            }

            // Count characters and write to output file
            char_count = strlen(buffer);
            fprintf(output_file, "Character Count: %d\n", char_count);
            fflush(output_file);

            // Write the result to pipe2 (to be read by Process 1)
            write(pipe2[1], buffer, bytes_read);
        }

        fclose(output_file);
        close(pipe1[0]);
        close(pipe2[1]);
    } else {
        // This is the parent process (Process 1)

        close(pipe1[0]);  // Close read end of pipe1
        close(pipe2[1]);  // Close write end of pipe2

        char input[MAX_BUF_SIZE];
        char output_buffer[MAX_BUF_SIZE];

        while (1) {
            // Accept sentences from the user
            printf("Enter a sentence (or 'exit' to quit): ");
            fgets(input, sizeof(input), stdin);

            // Exit the loop if the user enters "exit"
            if (strcmp(input, "exit\n") == 0) {
                break;
            }

            // Write the sentence to pipe1 (to be read by Process 2)
            write(pipe1[1], input, strlen(input));

            // Read the result from pipe2 (sent by Process 2) and display it
            ssize_t bytes_read = read(pipe2[0], output_buffer, MAX_BUF_SIZE);
            if (bytes_read <= 0) {
                break;  // End of input from Process 2
            }
            output_buffer[bytes_read] = '\0';

            printf("Received from Process 2: %s", output_buffer);
        }

        // Print the character count stored in the file by Process 2
        FILE *output_file = fopen("output.txt", "r");
        if (output_file != NULL) {
            char line[MAX_BUF_SIZE];
            while (fgets(line, sizeof(line), output_file)) {
                printf("%s", line);
            }
            fclose(output_file);
        }

        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL);  // Wait for Process 2 to finish
    }

    return 0;
}

