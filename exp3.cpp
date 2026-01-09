#include<stdio.h>

int main()
{
    // Declare arrays and variables
    int p[20], bt[20], wt[20], tat[20], i, k, n, temp; 
    float wtavg, tatavg;

    // Input: Number of processes
    printf("\nEnter the number of processes -- ");
    scanf("%d", &n);

    // Input: Burst time for each process
    for(i=0;i<n;i++)
    {
        p[i]=i; // Assign process ID
        printf("Enter Burst Time for Process %d -- ", i);
        scanf("%d", &bt[i]);
    }

    // Sort processes by burst time (SJF Logic)
    for(i=0;i<n;i++)
    {
        for(k=i+1;k<n;k++)
        {
            if(bt[i]>bt[k])
            {
                // Swap burst times
                temp=bt[i];
                bt[i]=bt[k];
                bt[k]=temp;
                // Swap process IDs
                temp=p[i];
                p[i]=p[k];
                p[k]=temp;
            }
        }            
    }
    
    // Initialize waiting and turnaround times for the first process
    wt[0] = wtavg = 0;
    tat[0] = tatavg = bt[0]; 
    
    for(i=1;i<n;i++)
    {
        // Calculate waiting and turnaround times for remaining processes
        wt[i] = wt[i-1] +bt[i-1]; // Waiting time = previous waiting + previous burst
        tat[i] = tat[i-1] +bt[i]; // Turnaround time = previous turnaround + current burst
        wtavg = wtavg + wt[i]; // Accumulate total waiting time
        tatavg = tatavg + tat[i]; // Accumulate total turnaround time
    }

    // Output: Process table
    printf("\n\t PROCESS \tBURST TIME \t WAITING TIME\t TURNAROUND TIME\n");
    for(i=0;i<n;i++)
        printf("\n\t P%d \t\t %d \t\t %d \t\t %d \n", p[i], bt[i], wt[i], tat[i]);

    // Output: Averages
    printf("\nAverage Waiting Time -- %f", wtavg/n);
    printf("\nAverage Turnaround Time -- %f", tatavg/n);

    return 0;
}
