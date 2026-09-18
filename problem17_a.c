#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    int ticket = 100;

    fd = open("ticket.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (write(fd, &ticket, sizeof(ticket)) == -1)
    {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Initial ticket number stored: %d\n", ticket);

    close(fd);

    return 0;
}

