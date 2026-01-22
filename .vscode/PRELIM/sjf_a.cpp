#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int pid[n], burst[n], wt[n], tat[n], completion[n];

    // Input burst times
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Burst Time for Process P" << pid[i] << ": ";
        cin >> burst[i];
    }

    // Simple SJF: sort processes by burst time
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
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
        wt[i] = wt[i-1] + burst[i-1];
        tat[i] = wt[i] + burst[i];
        completion[i] = completion[i-1] + burst[i];
    }

    float totalWT = 0, totalTAT = 0;
    cout << "\nPROCESS\tBURST\tWAITING\tTURNAROUND\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << burst[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    cout << "\nAverage Waiting Time: " << totalWT/n << endl;
    cout << "Average Turnaround Time: " << totalTAT/n << endl;

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
