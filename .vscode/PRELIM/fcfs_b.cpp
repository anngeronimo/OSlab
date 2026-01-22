#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int pid[n], arrival[n], burst[n], completion[n];

    // Input process data
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter arrival time of P" << pid[i] << ": ";
        cin >> arrival[i];
        cout << "Enter burst time of P" << pid[i] << ": ";
        cin >> burst[i];
    }

    // Simple FCFS: sort by arrival time
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (arrival[i] > arrival[j]) {
                swap(arrival[i], arrival[j]);
                swap(burst[i], burst[j]);
                swap(pid[i], pid[j]);
            }
        }
    }

    int currentTime = 0;
    double totalTAT = 0, totalWT = 0;

    cout << "\nProcess\tArrival\tBurst" << endl;

    // Calculate times
    for (int i = 0; i < n; i++) {
        if (currentTime < arrival[i])
            currentTime = arrival[i];

        completion[i] = currentTime + burst[i];
        int tat = completion[i] - arrival[i];
        int wt = tat - burst[i];

        totalTAT += tat;
        totalWT += wt;

        currentTime = completion[i];

        cout << "P" << pid[i] << "\t" << arrival[i] << "\t" << burst[i] << endl;
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "Average Waiting Time: " << totalWT / n << endl;

    // Gantt chart
    cout << "\nGantt Chart:\n|";
    for (int i = 0; i < n; i++)
        cout << " P" << pid[i] << " |";
    cout << "\n0";
    for (int i = 0; i < n; i++)
        cout << "\t" << completion[i];
    cout << endl;

    return 0;
}
