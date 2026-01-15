#include <stdio.h>      // Standard I/O functions (printf, etc.)
#include <stdlib.h>     // Standard library functions (exit, etc.)
#include <unistd.h>     // POSIX API for system calls (fork, execlp, getpid, etc.)
#include <sys/wait.h>   // For wait() system call

void main(int argc, char *arg[])
{
    int pid; // Variable to store the process ID returned by fork()

    // fork() system call: creates a new process by duplicating the calling process.
    // Returns: -1 on failure, 0 in the child process, and the child's PID in the parent process.
    pid = fork();

    if (pid < 0)
    {
        // fork() failed: print error and exit with status 1 (error)
        printf("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process: pid == 0
        // execlp() replaces the current process image with a new process image.
        // Here, it runs the "whoami" command, which prints the current user.
        // "whoami" is the command, "1s" is the first argument (though not used here), NULL terminates the argument list.
        // Note: "1s" seems like a typo; it should probably be "whoami" or another argument.
        execlp("whoami", "whoami", NULL);

        // If execlp() returns, it means it failed.
        // Exit the child process with status 0 (success).
        exit(0);
    }
    else
    {
        // Parent process: pid > 0
        // Print the parent's process ID.
        printf("\nProcess ID is: %d\n", getpid());

        // wait() system call: suspends execution of the calling process until one of its children terminates.
        // NULL means wait for any child process.
        wait(NULL);

        // Exit the parent process with status 0 (success).
        exit(0);
    }
}
