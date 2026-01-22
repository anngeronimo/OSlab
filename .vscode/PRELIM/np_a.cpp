#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int bt[20], wt[20], tat[20], priority[20], pid[20];

    // Input burst time and priority
    for (int i = 0; i < n; i++) {
        pid[i] = i;   // Original process ID
        cout << "Enter Burst Time for Process " << i << ": ";
        cin >> bt[i];
        cout << "Enter Priority for Process " << i << ": ";
;
        cin >> priority[i];
    }

    // Sort by priority (Non-preemptive)
    for (int i = 0; i < n - 1; i++) {
        int pos = i;
        for (int j = i + 1; j < n; j++) {
            if (priority[j] < priority[pos])
                pos = j;
        }

        // Swap burst time
        swap(bt[i], bt[pos]);
        // Swap priority
        swap(priority[i], priority[pos]);
        // Swap process ID
        swap(pid[i], pid[pos]);
    }

    // Calculate Waiting Time and Turnaround Time
    wt[0] = 0;
    tat[0] = bt[0];

    float totalWT = wt[0];
    float totalTAT = tat[0];

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n|";
    for (int i = 0; i < n; i++) {
        cout << "  P" << pid[i] << "  |";
    }
    cout << "\n0";
    for (int i = 0; i < n; i++) {
        cout << "     " << tat[i];
    }
    cout << endl;

    // Display process table
    cout << "\nPROCESS\tBURST\tPRIORITY\tWAITING\tTURNAROUND\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t"
             << bt[i] << "\t"
             << priority[i] << "\t\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    // Averages
    cout << "\nAverage Waiting Time: " << totalWT / n << endl;
    cout << "Average Turnaround Time: " << totalTAT / n << endl;

    return 0;
}
