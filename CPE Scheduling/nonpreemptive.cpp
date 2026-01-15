#include <stdio.h>

int main() {
    int bt[20], wt[20], tat[20], p[20], proc[20], i, j, n, temp, pos;
    float wtavg = 0, tatavg = 0;

    printf("Enter the number of processes -- ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        proc[i] = i;  // Store original process ID
        printf("Enter Burst Time for Process %d -- ", i);
        scanf("%d", &bt[i]);
        printf("Enter Priority for Process %d (lower number = higher priority) -- ", i);
        scanf("%d", &p[i]);
    }

    // Sort processes by priority (non-preemptive priority scheduling)
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (p[j] < p[pos])
                pos = j;
        }

        // Swap burst time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap priority
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;

        // Swap process ID
        temp = proc[i];
        proc[i] = proc[pos];
        proc[pos] = temp;
    }

    // Calculate waiting time and turnaround time
    wt[0] = 0;
    tat[0] = bt[0];
    wtavg += wt[0];
    tatavg += tat[0];

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    printf("|");
    for (i = 0; i < n; i++) {
        printf("   P%d   |", proc[i]);
    }
    printf("\n");

    printf("0");
    for (i = 0; i < n; i++) {
        printf("      %d", tat[i]);
    }
    printf("\n");

    // Print process details
    printf("\n\t PROCESS \tBURST TIME \t PRIORITY \t WAITING TIME\t TURNAROUND TIME\n");
    for (i = 0; i < n; i++)
        printf("\n\t P%d \t\t %d \t\t %d \t\t %d \t\t %d", proc[i], bt[i], p[i], wt[i], tat[i]);

    // Print averages
    printf("\nAverage Waiting Time -- %f", wtavg / n);
    printf("\nAverage Turnaround Time -- %f", tatavg / n);

    return 0;
}