#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <numeric>

using namespace std;

struct Process {
    int pid;        
    int at;   
    int bt;     
    int remaining; 
    int completion; 
    int tat;
    int wt;    
};

void displayTable(const vector<Process>& processes) {
    cout << "| Process  | Arrival | Burst  | Completion  | Turnaround  | Waiting   |\n";
    for (const auto& p : processes) {
        cout << "| " << setw(8) << p.pid
             << " | " << setw(7) << p.at
             << " | " << setw(6) << p.bt
             << " | " << setw(11) << p.completion
             << " | " << setw(11) << p.tat
             << " | " << setw(9) << p.wt << " |\n";
    }
}

void calculate(vector<Process>& processes) {
    for (auto& p : processes) {
        p.tat = p.completion - p.at;
        p.wt = p.tat - p.bt;
    }
}

int recommendedTimeQuantum(const vector<int>& burst_times) {
    int sum = accumulate(burst_times.begin(), burst_times.end(), 0);
    return sum / burst_times.size();
}

void roundRobin(vector<Process> processes, int quantum) {
    queue<int> q;
    vector<Process> result = processes;
    int time = 0;
    int completed = 0;
    vector<bool> visited(processes.size(), false);

    while (completed != processes.size()) {
        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].at <= time && !visited[i] && result[i].remaining > 0) {
                q.push(i);
                visited[i] = true;
            }
        }

        if (!q.empty()) {
            int idx = q.front();
            q.pop();
            int exec = min(quantum, result[idx].remaining);
            time += exec;
            result[idx].remaining -= exec;

            if (result[idx].remaining == 0) {
                result[idx].completion = time;
                completed++;
            } else {
                q.push(idx);
            }
        } else {
            time++;
        }
    }

    calculate(result);
    cout << "\nRound Robin (Recommended Time Quantum = " << quantum << "):\n";
    displayTable(result);

    double avg_tat = 0, avg_wt = 0;
    for (const auto& p : result) {
        avg_tat += p.tat;
        avg_wt += p.wt;
    }
    avg_tat /= result.size();
    avg_wt /= result.size();
    cout << "\nAverage Turnaround Time: " << avg_tat << endl;
    cout << "Average Waiting Time: " << avg_wt << endl;
}

void sjf(vector<Process> processes) {
    vector<Process> result = processes;
    vector<bool> completed(processes.size(), false);
    int time = 0, completed_count = 0;

    while (completed_count != processes.size()) {
        int shortest = -1, min_burst = INT_MAX;
        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].at <= time && !completed[i] && processes[i].bt < min_burst) {
                min_burst = processes[i].bt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        time += result[shortest].bt;
        result[shortest].completion = time;
        completed[shortest] = true;
        completed_count++;
    }

    calculate(result);
    cout << "\nShortest Job First:\n";
    displayTable(result);

    double avg_tat = 0, avg_wt = 0;
    for (const auto& p : result) {
        avg_tat += p.tat;
        avg_wt += p.wt;
    }
    avg_tat /= result.size();
    avg_wt /= result.size();
    cout << "\nAverage Turnaround Time: " << avg_tat << endl;
    cout << "Average Waiting Time: " << avg_wt << endl;
}

void srtf(vector<Process> processes) {
    vector<Process> result = processes;
    for (auto& p : result) p.remaining = p.bt;
    int time = 0, completed = 0;

    while (completed != processes.size()) {
        int shortest = -1, min_remaining = INT_MAX;
        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].at <= time && result[i].remaining > 0 && result[i].remaining < min_remaining) {
                min_remaining = result[i].remaining;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        result[shortest].remaining--;
        time++;

        if (result[shortest].remaining == 0) {
            result[shortest].completion = time;
            completed++;
        }
    }

    calculate(result);
    cout << "\nShortest Remaining Time First:\n";
    displayTable(result);

    double avg_tat = 0, avg_wt = 0;
    for (const auto& p : result) {
        avg_tat += p.tat;
        avg_wt += p.wt;
    }
    avg_tat /= result.size();
    avg_wt /= result.size();
    cout << "\nAverage Turnaround Time: " << avg_tat << endl;
    cout << "Average Waiting Time: " << avg_wt << endl;
}

int main() {
    vector<int> burst_times = {53, 43, 18, 16, 44, 73, 99, 27};
    vector<int> arrival_times = {4, 2, 3, 6, 1, 5, 8, 7};
    vector<Process> processes;

    for (int i = 0; i < burst_times.size(); ++i) {
        processes.push_back({i+1, arrival_times[i], burst_times[i], burst_times[i], 0, 0, 0});
    }

    int mean_quantum = recommendedTimeQuantum(burst_times);

    cout << "Mean Quantum: " << mean_quantum << endl;

    roundRobin(processes, mean_quantum);
    sjf(processes);
    srtf(processes);

    return 0;
}
