#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    // First fork: creates a child process, now there are 2 processes running
    fork();

    // Second fork: each of the 2 processes calls fork(), creating 2 more processes, total 4
    fork();

    // Each of the 4 processes prints its own Process ID (PID)
    cout << "PID: " << getpid() << endl;

    // Each process waits for one of its child processes to finish
    // This prevents "zombie" processes and ensures proper synchronization
    wait(NULL);

    // Another wait to ensure all child processes are waited for
    wait(NULL);

    // Exit the process successfully
    return 0;
}
