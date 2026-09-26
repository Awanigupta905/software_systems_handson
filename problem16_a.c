#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd;
    struct flock lock;

    fd = open("lab16.txt", O_RDWR | O_CREAT, 0660);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (fchmod(fd, 02660) == -1) {
        perror("fchmod");
        close(fd);
        return 1;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;      

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Mandatory write lock acquired.\n");
    printf("Sleeping for 15 seconds...\n");

    sleep(15);

    close(fd);

    printf("Write lock released.\n");

    return 0;
}

