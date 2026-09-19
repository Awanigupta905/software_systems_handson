#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    errno = 0;

    int priority = nice(0);

    if (errno != 0)
    {
        perror("nice");
        return 1;
    }

    printf("Process ID: %d\n", getpid());
    printf("Current nice value: %d\n", priority);

    return 0;
}

