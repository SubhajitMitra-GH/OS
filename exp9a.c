#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

void findWaitingTime(struct Process processes[], int n) {
    int completed = 0, t = 0;

    while (completed < n) {
        int highest_priority_index = -1;
        int highest_priority = 9999;

        // Find the highest priority process that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= t && processes[i].waiting_time == -1 && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
            }
        }

        // If no process has arrived, increase time
        if (highest_priority_index == -1) {
            t++;
            continue;
        }

        // Execute the process with the highest priority
        struct Process *p = &processes[highest_priority_index];
        t += p->burst_time;
        p->waiting_time = t - p->arrival_time - p->burst_time;
        if (p->waiting_time < 0) {
            p->waiting_time = 0;
        }
        p->turnaround_time = p->burst_time + p->waiting_time;

        completed++;
    }
}

void findAverageTime(struct Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    findWaitingTime(processes, n);

    printf("Processes  Arrival Time  Burst Time  Priority  Waiting Time  Turn-Around Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("   %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("Average waiting time = %.2f\n", (float)total_waiting_time / n);
    printf("Average turn-around time = %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        processes[i].waiting_time = -1; // Initialize waiting time as -1 to indicate not yet completed
        printf("Enter arrival time, burst time and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    }

    findAverageTime(processes, n);
    return 0;
}
