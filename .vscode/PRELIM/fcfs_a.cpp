#include <iostream>
using namespace std;

int main() {
    int n = 5;

    // Process arrival and burst times
    int arrivalTime[5] = {0, 1, 2, 4, 6};
    int burstTime[5]   = {3, 5, 2, 1, 4};

    int currentTime = 0;
    double totalTAT = 0.0;
    double totalWT = 0.0;

    int completionTime[5];

    cout << "Process\tArrival\tBurst" << endl;

    // Calculate completion, TAT, and WT
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t" << arrivalTime[i] << "\t" << burstTime[i] << endl;

        // If CPU is idle, move current time to arrival
        if (currentTime < arrivalTime[i])
            currentTime = arrivalTime[i];

        completionTime[i] = currentTime + burstTime[i];

        int turnaroundTime = completionTime[i] - arrivalTime[i];
        int waitingTime = turnaroundTime - burstTime[i];

        totalTAT += turnaroundTime;
        totalWT += waitingTime;

        currentTime = completionTime[i];
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "Average Waiting Time: " << totalWT / n << endl;

    // ---------- Gantt Chart ----------
    cout << "\nGantt Chart:\n";
    cout << "|";

    // Print process sequence
    for (int i = 0; i < n; i++) {
        cout << " P" << i+1 << " |";
    }
    cout << "\n";

    // Print time markers
    cout << "0";  // start time
    for (int i = 0; i < n; i++) {
        cout << "    " << completionTime[i];
    }
    cout << endl;

    return 0;
}
