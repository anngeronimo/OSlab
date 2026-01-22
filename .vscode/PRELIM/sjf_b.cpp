#include <iostream>
using namespace std;

int main() {
    int n = 5;

    // Declared process data
    int pid[5]   = {1, 2, 3, 4, 5};
    int burst[5] = {6, 8, 7, 3, 4};

    int wt[5], tat[5], completion[5];

    // Sort processes by Burst Time (SJF)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (burst[i] > burst[j]) {
                swap(burst[i], burst[j]);
                swap(pid[i], pid[j]);
            }
        }
    }

    // Calculate Waiting Time and Turnaround Time
    wt[0] = 0;
    tat[0] = burst[0];
    completion[0] = burst[0];

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + burst[i - 1];
        tat[i] = wt[i] + burst[i];
        completion[i] = completion[i - 1] + burst[i];
    }

    float totalWT = 0, totalTAT = 0;

    cout << "PROCESS\tBURST\tWAITING\tTURNAROUND\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t"
             << burst[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;

        totalWT += wt[i];
        totalTAT += tat[i];
    }

    cout << "\nAverage Waiting Time: " << totalWT / n << endl;
    cout << "Average Turnaround Time: " << totalTAT / n << endl;

    // Gantt Chart
    cout << "\nGantt Chart:\n|";
    for (int i = 0; i < n; i++)
        cout << " P" << pid[i] << " |";

    cout << "\n0";
    for (int i = 0; i < n; i++)
        cout << "\t" << completion[i];
    cout << endl;

    return 0;
}
