#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    int ticket;
    struct flock lock;

    fd = open("ticket.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    printf("Requesting write lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Write lock acquired.\n");

    if (read(fd, &ticket, sizeof(ticket)) == -1)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    ticket++;

    printf("New ticket number: %d\n", ticket);

    lseek(fd, 0, SEEK_SET);

    if (write(fd, &ticket, sizeof(ticket)) == -1)
    {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLK, &lock) == -1)
    {
        perror("unlock");
    }

    printf("Write lock released.\n");

    close(fd);

    return 0;
}

