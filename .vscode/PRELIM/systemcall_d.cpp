#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    // Loop to create 3 child processes
    for (int i = 0; i < 3; i++)
    {
        pid_t pid = fork();

        // This block runs only in the child process
        if (pid == 0)
        {
            cout << "Child PID: " << getpid()
                 << " | Parent PID: " << getppid() << endl;
            return 0; // Child exits so it does not create more children
        }
    }

    // Parent waits for all 3 child processes to finish
    for (int i = 0; i < 3; i++)
    {
        wait(NULL);
    }

    cout << "Parent PID: " << getpid() << endl;

    return 0;
}
