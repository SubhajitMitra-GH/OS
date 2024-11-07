#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void findAverageTime(struct Process processes[], int n, int time_quantum) {
    int t = 0;           // Current time
    int completed = 0;   // Number of processes completed

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
    }

    // Perform round-robin scheduling
    while (completed < n) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            // Only consider processes that have arrived and have remaining time
            if (processes[i].arrival_time <= t && processes[i].remaining_time > 0) {
                done = 0;
                if (processes[i].remaining_time > time_quantum) {
                    // Process is executed for a full time quantum
                    t += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } else {
                    // Process finishes within the time quantum
                    t += processes[i].remaining_time;
                    processes[i].waiting_time = t - processes[i].arrival_time - processes[i].burst_time;
                    processes[i].turnaround_time = t - processes[i].arrival_time;
                    processes[i].remaining_time = 0;
                    completed++;
                }
            }
        }

        // If all processes are completed, break out of loop
        if (done) break;
    }

    // Calculate and display results
    int total_waiting_time = 0, total_turnaround_time = 0;
    printf("Processes  Arrival Time  Burst Time  Waiting Time  Turn-Around Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("   %d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("Average waiting time = %.2f\n", (float)total_waiting_time / n);
    printf("Average turn-around time = %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n, time_quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    findAverageTime(processes, n, time_quantum);
    return 0;
}
