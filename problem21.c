#include <stdio.h>
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
        printf("Child Process\n");
        printf("Child Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
    }
    else
    {
        printf("Parent Process\n");
        printf("Parent Process ID: %d\n", getpid());
        printf("Child Process ID: %d\n", pid);
    }

    return 0;
}

