#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 256

int main(int argc, char *argv[])
{
    int fd;
    struct flock lock;
    char buf[BUF_SIZE];
    ssize_t n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* Set up a shared read lock covering the whole file */
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    printf("[reader] Requesting read lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl (read lock)");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("[reader] Read lock acquired. Reading and holding for 10 seconds...\n");

    n = read(fd, buf, BUF_SIZE - 1);

    if (n > 0) {
        buf[n] = '\0';
        printf("[reader] Read: %s", buf);
    }

    sleep(10);

    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl (unlock)");
    }

    printf("[reader] Lock released.\n");

    close(fd);

    return 0;
}

