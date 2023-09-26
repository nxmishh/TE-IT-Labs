#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

// Function to perform Shortest Job First (Preemptive) scheduling
void sjfPreemptive(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;
    int ganttChart[100]; // Array to store process IDs for Gantt chart

    while (completed < n) {
        int minBurstTime = INT_MAX;
        int shortestJob = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].remaining_time < minBurstTime && processes[i].remaining_time > 0) {
                minBurstTime = processes[i].remaining_time;
                shortestJob = i;
            }
        }

        if (shortestJob == -1) {
            currentTime++;
        } else {
            processes[shortestJob].remaining_time--;
            ganttChart[currentTime] = processes[shortestJob].id; // Store the process ID in the Gantt chart
            currentTime++;

            if (processes[shortestJob].remaining_time == 0) {
                completed++;
                int turnaroundTime = currentTime - processes[shortestJob].arrival_time;
                int waitingTime = turnaroundTime - processes[shortestJob].burst_time;
                printf("Process %d: Turnaround Time = %d, Waiting Time = %d\n", processes[shortestJob].id, turnaroundTime, waitingTime);
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
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nShortest Job First (Preemptive) Scheduling:\n");
    sjfPreemptive(processes, n);

    return 0;
}

