#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        printf("Child Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Initial Parent PID: %d\n", getppid());

        printf("Child is sleeping...\n");
        sleep(10);

        printf("Child PID: %d\n", getpid());
        printf("New Parent PID: %d\n", getppid());
        printf("Child has become an orphan process.\n");
    }
    else
    {
        // Parent process
        printf("Parent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent is exiting...\n");
        exit(0);
    }

    return 0;
}

