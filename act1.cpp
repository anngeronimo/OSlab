// Include standard input/output library for functions like printf
#include <stdio.h>
// Include standard library for functions like exit
#include <stdlib.h>
// Include unistd.h for system calls like fork, getpid, and execlp
#include <unistd.h>
// Include sys/wait.h for the wait system call
#include <sys/wait.h>

// Main function with command-line arguments (not used in this program)
void main(int argc, char *arg[])
{
    int pid; // Declare an integer variable to store the process ID

    // fork() system call creates a new process by duplicating the calling process.
    // The new process is referred to as the child and the calling process is referred to as the parent.
    // On success, fork() returns the PID of the child process in the parent's context,
    // and 0 in the child's context.
    // On failure, fork() returns -1.
    pid = fork();

    // Check if fork() failed (pid < 0)
    if (pid < 0)
    {
        // Print error message if fork() fails
        printf("fork failed");
        // Exit the program with status 1 (indicating an error)
        exit(1);
    }
    // If pid == 0, this is the child process
    else if (pid == 0)
    {
        // execlp() replaces the current process image with a new process image.
        // Here, it runs the "whoami" command, which prints the current user.
        // The second argument "1s" is a typo; it should be "whoami" or omitted.
        // NULL marks the end of the arguments.
        // If execlp() succeeds, the following code is not executed.
        execlp("whoami", "whoami", NULL);
        // If execlp() fails, exit the child process with status 0
        exit(0);
    }
    // If pid > 0, this is the parent process
    else
    {
        // Print the process ID of the parent process using getpid()
        printf("\n Process ID is:   %d\n", getpid());
        // wait() system call makes the parent process wait until the child process terminates.
        // NULL means the parent does not need the child's exit status.
        wait(NULL);
        // Exit the parent process with status 0 (indicating success)
        exit(0);
    }
}
