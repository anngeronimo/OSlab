#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    pid_t pid1, pid2;

    // Parent creates first child
    pid1 = fork();

    if (pid1 == 0)
    {
        // First child process
        sleep(1); // Delay to make it finish last
        cout << "First Child PID: " << getpid()
             << " | Parent PID: " << getppid() << endl;
        return 0;
    }

    // Parent creates second child
    pid2 = fork();

    if (pid2 == 0)
    {
        // Second child process
        cout << "Second Child PID: " << getpid()
             << " | Parent PID: " << getppid() << endl;
        return 0;
    }

    // Parent process (only one parent)
    cout << "Parent PID: " << getpid() << endl;

    // Parent waits for both children
    wait(NULL);
    wait(NULL);

    return 0;
}
