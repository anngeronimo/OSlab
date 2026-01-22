#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        execlp("ls", "ls", NULL);
    }
    else
    {
        wait(NULL);
        cout << "Child process completed" << endl;
    }

    return 0;
}
