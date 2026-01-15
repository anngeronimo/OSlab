#include <stdio.h>

int main()
{
    int bt[20], wt[20], tat[20], rem_bt[20], i, n, tq, time = 0;
    float wtavg = 0, tatavg = 0;
    int gantt[100], gantt_time[100], g_idx = 0;  // For Gantt chart

    // Input: Number of processes
    printf("Enter the number of processes -- ");
    scanf("%d", &n);

    // Input: Burst time for each process
    for(i=0; i<n; i++)
    {
        printf("Enter Burst Time for Process %d -- ", i);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i]; // Copy burst time to remaining burst time
    }

    // Input: Time Quantum
    printf("\nEnter Time Quantum -- ");
    scanf("%d", &tq);

    // Initialize waiting time and turnaround time
    for(i=0; i<n; i++)
    {
        wt[i] = 0;
        tat[i] = 0;
    }

    // Round Robin Scheduling
    while(1)
    {
        int done = 1; // Flag to check if all processes are done

        for(i=0; i<n; i++)
        {
            if(rem_bt[i] > 0)
            {
                done = 0; // There is a process not yet done

                if(rem_bt[i] > tq)
                {
                    time += tq;
                    rem_bt[i] -= tq;
                    // Add to Gantt chart
                    gantt[g_idx] = i;
                    gantt_time[g_idx] = time;
                    g_idx++;
                }
                else
                {
                    time += rem_bt[i];
                    wt[i] = time - bt[i];
                    rem_bt[i] = 0;
                    // Add to Gantt chart
                    gantt[g_idx] = i;
                    gantt_time[g_idx] = time;
                    g_idx++;
                }
            }
        }

        if(done == 1) // All processes are done
            break;
    }

    // Calculate Turnaround Time and Averages
    for(i=0; i<n; i++)
    {
        tat[i] = wt[i] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    printf("0");
    for(i=0; i<g_idx; i++)
    {
        printf(" -- P%d -- %d", gantt[i], gantt_time[i]);
    }
    printf("\n");

    // Output: Process details
    printf("\n\t PROCESS \tBURST TIME \t WAITING TIME\t TURNAROUND TIME\n");
    for(i=0; i<n; i++)
        printf("\n\t P%d \t\t %d \t\t %d \t\t %d", i, bt[i], wt[i], tat[i]);

    // Output: Averages
    printf("\n\nAverage Waiting Time -- %f", wtavg/n);
    printf("\nAverage Turnaround Time -- %f", tatavg/n);

    return 0;
}