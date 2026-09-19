#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main()
{
    int fd;
    pid_t pid;

    // Open the file
    fd = open("output22.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        close(fd);
        return 1;
    }

    if (pid == 0)
    {
        // Child process writes to the file
        write(fd, "Written by Child Process\n", 25);
        printf("Child process wrote to the file.\n");
    }
    else
    {
        // Parent process writes to the file
        write(fd, "Written by Parent Process\n", 26);
        printf("Parent process wrote to the file.\n");
    }

    close(fd);

    return 0;
}

