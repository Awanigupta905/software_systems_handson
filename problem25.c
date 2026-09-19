#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t child1, child2, child3;

    // Create first child
    child1 = fork();

    if (child1 < 0)
    {
        perror("fork");
        return 1;
    }

    if (child1 == 0)
    {
        printf("Child 1: PID = %d\n", getpid());
        sleep(2);
        printf("Child 1 exiting...\n");
        exit(1);
    }

    // Create second child
    child2 = fork();

    if (child2 < 0)
    {
        perror("fork");
        return 1;
    }

    if (child2 == 0)
    {
        printf("Child 2: PID = %d\n", getpid());
        sleep(5);
        printf("Child 2 exiting...\n");
        exit(2);
    }

    // Create third child
    child3 = fork();

    if (child3 < 0)
    {
        perror("fork");
        return 1;
    }

    if (child3 == 0)
    {
        printf("Child 3: PID = %d\n", getpid());
        sleep(3);
        printf("Child 3 exiting...\n");
        exit(3);
    }

    // Parent process
    printf("Parent: PID = %d\n", getpid());
    printf("Child 1 PID = %d\n", child1);
    printf("Child 2 PID = %d\n", child2);
    printf("Child 3 PID = %d\n", child3);

    // Parent waits specifically for Child 2
    printf("Parent waiting for Child 2...\n");

    int status;

    if (waitpid(child2, &status, 0) == -1)
    {
        perror("waitpid");
        return 1;
    }

    printf("Parent: Child 2 has terminated.\n");

    if (WIFEXITED(status))
    {
        printf("Child 2 exit status = %d\n", WEXITSTATUS(status));
    }

    // Wait for the remaining children
    waitpid(child1, NULL, 0);
    waitpid(child3, NULL, 0);

    printf("Parent: All children have terminated.\n");

    return 0;
}

