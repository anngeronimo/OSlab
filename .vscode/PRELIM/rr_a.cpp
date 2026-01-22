#include <iostream>
using namespace std;

int main()
{
    int n = 4;                 // Number of processes
    float tq = 2;              // Time Quantum

    // Declared burst times
    float bt[4] = {5, 4, 2, 1};
    float rem_bt[4];
    float wt[4] = {0}, tat[4] = {0};

    float time = 0;
    float wtavg = 0, tatavg = 0;

    // For Gantt chart
    int gantt[100], gantt_time[100], g_idx = 0;

    // Copy burst time
    for(int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    // Round Robin Scheduling
    while (1)
    {
        int done = 1;

        for (int i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = 0;

                if (rem_bt[i] > tq)
                {
                    time += tq;
                    rem_bt[i] -= tq;
                }
                else
                {
                    time += rem_bt[i];
                    wt[i] = time - bt[i];
                    rem_bt[i] = 0;
                }

                gantt[g_idx] = i;
                gantt_time[g_idx] = time;
                g_idx++;
            }
        }

        if (done == 1)
            break;
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // ===== FIXED GANTT CHART =====
    cout << "\nGantt Chart:\n|";
    for (int i = 0; i < g_idx; i++)
        cout << "  P" << gantt[i] << "  |";

    cout << "\n0";
    for (int i = 0; i < g_idx; i++)
        cout << "     " << gantt_time[i];
    cout << "\n";

    // Process table
    cout << "\nPROCESS\tBURST\tWAITING\tTURNAROUND\n";
    for (int i = 0; i < n; i++)
        cout << "P" << i << "\t"
             << bt[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;

    // Averages
    cout << "\nAverage Waiting Time -- " << wtavg / n;
    cout << "\nAverage Turnaround Time -- " << tatavg / n << endl;

    return 0;
}
