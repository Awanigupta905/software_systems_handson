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

        printf("Child is exiting...\n");
        exit(0);
    }
    else
    {
        // Parent process
        printf("Parent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent is sleeping for 30 seconds...\n");

        // Parent does not call wait()
        // Therefore, child becomes a zombie
        sleep(30);

        printf("Parent is exiting...\n");
    }

    return 0;
}

