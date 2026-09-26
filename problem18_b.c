#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("lab18.txt", O_RDONLY);

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 8;
    lock.l_len = 8;

    fcntl(fd, F_SETLKW, &lock);
    lseek(fd, 8, SEEK_SET);
    char buf[9];
    read(fd, buf, 8);
    buf[8] = '\0';
    printf("Record 1: %s\n", buf);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return 0;
}

