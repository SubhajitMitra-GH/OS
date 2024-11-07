#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[]) {
    int completed = 0, t = 0, min_burst = 9999;
    int shortest = 0, finish_time;
    int completed_processes[n];
    for (int i = 0; i < n; i++) {
        completed_processes[i] = 0;
    }

    while (completed != n) {
        // Find the shortest process that has arrived
        shortest = -1;
        min_burst = 9999;
        for (int i = 0; i < n; i++) {
            if (at[i] <= t && !completed_processes[i] && bt[i] < min_burst) {
                min_burst = bt[i];
                shortest = i;
            }
        }

        // If no process is found that has arrived by time `t`, increase time
        if (shortest == -1) {
            t++;
            continue;
        }

        // Process the shortest job
        t += bt[shortest];
        wt[shortest] = t - at[shortest] - bt[shortest];
        if (wt[shortest] < 0) {
            wt[shortest] = 0;
        }

        completed_processes[shortest] = 1;
        completed++;
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAverageTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt, at);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("Processes  Arrival Time  Burst Time  Waiting Time  Turn-Around Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turn-around time = %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], arrival_time[n];
    
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
    }

    findAverageTime(processes, n, burst_time, arrival_time);
    return 0;
}
