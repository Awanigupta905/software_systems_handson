#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    struct flock lock;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Open read-write */
    fd = open(argv[1], O_RDWR);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* Set up an exclusive write lock covering the whole file */
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    printf("[writer] Requesting write lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl (write lock)");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("[writer] Write lock acquired. Writing and holding for 10 seconds...\n");

    const char *msg = "Written by writelock process\n";

    write(fd, msg, strlen(msg));

    sleep(10);

    /* Release the lock */
    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl (unlock)");
    }

    printf("[writer] Lock released.\n");

    close(fd);

    return 0;
}

