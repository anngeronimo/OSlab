// Include the standard input-output library for functions like printf and scanf
#include<stdio.h>

// Main function: Entry point of the program
main()
{
    // Declare arrays and variables:
    // bt[]: Burst time for each process
    // wt[]: Waiting time for each process
    // tat[]: Turnaround time for each process
    // i: Loop counter
    // n: Number of processes
    // wtavg: Average waiting time
    // tatavg: Average turnaround time
    int bt[20], wt[20], tat[20], i, n;
    float wtavg, tatavg;

    // Prompt user to enter the number of processes
    printf("\nEnter the number of processes -- ");
    scanf("%d", &n);

    // Loop to input burst time for each process
    for(i=0; i<n; i++)
    {
        printf("\nEnter Burst Time for Process %d -- ", i);
        scanf("%d", &bt[i]);
    }

    // Initialize waiting time and turnaround time for the first process
    // The first process has no waiting time, and its turnaround time is equal to its burst time
    wt[0] = wtavg = 0;
    tat[0] = tatavg = bt[0];

    // Loop to calculate waiting time and turnaround time for the remaining processes
    for(i=1; i<n; i++)
    {
        // Waiting time for process i is the sum of waiting time and burst time of previous process
        wt[i] = wt[i-1] + bt[i-1];
        // Turnaround time for process i is the sum of turnaround time of previous process and burst time of current process
        tat[i] = tat[i-1] + bt[i];
        // Accumulate waiting time and turnaround time for average calculation
        wtavg = wtavg + wt[i];
        tatavg = tatavg + tat[i];
    }

    // Print the table header
    printf("\t PROCESS \tBURST TIME \t WAITING TIME\t TURNAROUND TIME\n");

    // Loop to print process details: process number, burst time, waiting time, turnaround time
    for(i=0; i<n; i++)
        printf("\n\t P%d \t\t %d \t\t %d \t\t %d", i, bt[i], wt[i], tat[i]);

    // Print the average waiting time and average turnaround time
    printf("\nAverage Waiting Time -- %f", wtavg/n);
    printf("\nAverage Turnaround Time -- %f", tatavg/n);
}
