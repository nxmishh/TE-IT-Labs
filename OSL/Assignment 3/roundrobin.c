#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
};

// Function to perform Round Robin scheduling
void roundrobin(struct Process processes[], int n, int timeQuantum) {
    int currentTime = 0;
    int completed = 0;
    int ganttChart[100]; // Array to store process IDs for Gantt chart

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].burst_time > 0) {
                int executionTime;
                if (processes[i].burst_time < timeQuantum) {
                    executionTime = processes[i].burst_time;
                } else {
                    executionTime = timeQuantum;
                }
                currentTime += executionTime;
                processes[i].burst_time -= executionTime;

                // Store the process ID in the Gantt chart
                for (int j = currentTime - executionTime; j < currentTime; j++) {
                    ganttChart[j] = processes[i].id;
                }

                if (processes[i].burst_time == 0) {
                    processes[i].completion_time = currentTime;
                    printf("Process %d: Arrival Time = %d, Completion Time = %d\n", processes[i].id, processes[i].arrival_time, processes[i].completion_time);
                    completed++;
                }
            }
        }
    }


    // Print Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < currentTime; i++) {
        printf("P%d ", ganttChart[i]);
    }
    printf("\n");
}

int main() {
    int n, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
    }

    printf("\nEnter the time quantum for Round Robin: ");
    scanf("%d", &timeQuantum);

    roundrobin(processes, n, timeQuantum);

    return 0;
}

