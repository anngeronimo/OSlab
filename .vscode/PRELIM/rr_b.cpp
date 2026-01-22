#include <iostream>
using namespace std;

int main()
{
    int n;
    float tq;

    float bt[20], rem_bt[20], wt[20], tat[20];
    float time = 0, wtavg = 0, tatavg = 0;

    // For Gantt Chart
    int gantt[100], gantt_time[100], g_idx = 0;

    // Input number of processes
    cout << "Enter the number of processes -- ";
    cin >> n;

    // Input burst times
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Burst Time for Process " << i << " -- ";
        cin >> bt[i];
        rem_bt[i] = bt[i];
        wt[i] = 0;
        tat[i] = 0;
    }

    // Input time quantum
    cout << "\nEnter Time Quantum -- ";
    cin >> tq;

    // Round Robin Scheduling
    while (true)
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

                // Store Gantt chart data
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

    // ===== FIXED GANTT CHART (SAME STYLE AS OTHERS) =====
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
