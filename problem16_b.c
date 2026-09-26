#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd = open("lab16.txt", O_RDWR | O_CREAT, 0660);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Mandatory locking:
    // Set-group-ID bit ON, group-execute bit OFF
    if (fchmod(fd, 02660) == -1) {
        perror("fchmod");
        close(fd);
        return 1;
    }

    struct flock lock;

    lock.l_type = F_RDLCK;      // Read lock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;             // Entire file

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Mandatory read lock acquired, sleeping 15s\n");

    sleep(15);

    close(fd);

    printf("Read lock released\n");

    return 0;
}

