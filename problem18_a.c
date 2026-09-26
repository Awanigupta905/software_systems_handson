#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("lab18.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    char *records[3] = {"record0\n", "record1\n", "record2\n"};
    for (int i = 0; i < 3; i++)
        write(fd, records[i], strlen(records[i]));

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 8;
    lock.l_len = 8;

    fcntl(fd, F_SETLKW, &lock);
    lseek(fd, 8, SEEK_SET);
    write(fd, "RECORD1!\n", 9);

    sleep(30);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return 0;
}

