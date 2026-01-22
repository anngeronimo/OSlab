#include <iostream>
using namespace std;

int main() {
    int n = 5;

    // Declared process data
    int pid[5]      = {0, 1, 2, 3, 4};
    int burst[5]    = {5, 3, 4, 2, 6};
    int priority[5] = {2, 1, 3, 2, 4}; 
    // Lower number = higher priority

    int wt[5], tat[5];

    // Sort by priority (Non-preemptive)
    for (int i = 0; i < n - 1; i++) {
        int pos = i;
        for (int j = i + 1; j < n; j++) {
            if (priority[j] < priority[pos])
                pos = j;
        }

        swap(priority[i], priority[pos]);
        swap(burst[i], burst[pos]);
        swap(pid[i], pid[pos]);
    }

    // Calculate Waiting Time and Turnaround Time
    wt[0] = 0;
    tat[0] = burst[0];

    float totalWT = 0, totalTAT = tat[0];

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + burst[i - 1];
        tat[i] = tat[i - 1] + burst[i];
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    // Display process table
    cout << "PROCESS\tBURST\tPRIORITY\tWAITING\tTURNAROUND\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t"
             << burst[i] << "\t"
             << priority[i] << "\t\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    // Averages
    cout << "\nAverage Waiting Time: " << totalWT / n << endl;
    cout << "Average Turnaround Time: " << totalTAT / n << endl;

    // Gantt Chart
    cout << "\nGantt Chart:\n|";
    for (int i = 0; i < n; i++)
        cout << "  P" << pid[i] << "  |";

    cout << "\n0";
    for (int i = 0; i < n; i++)
        cout << "     " << tat[i];
    cout << endl;

    return 0;
}
