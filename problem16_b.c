#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd = open("lab16.txt", O_RDWR | O_CREAT, 0644);

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    fcntl(fd, F_SETLK, &lock);
    printf("Read lock acquired, sleeping 15s \n");
    sleep(15);

    close(fd);
    return 0;
}



