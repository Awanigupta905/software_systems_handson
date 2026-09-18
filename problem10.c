#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    off_t position;
    char data1[] = "1234567890";
    char data2[] = "ABCDEFGHIJ";

    // Open file in read-write mode
    fd = open("file10.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write first 10 bytes
    write(fd, data1, 10);

    // Move file pointer forward by 10 bytes
    position = lseek(fd, 10, SEEK_CUR);

    // Check return value of lseek
    if (position == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("File pointer position after lseek: %ld\n", position);

    // Write another 10 bytes
    write(fd, data2, 10);

    close(fd);

    return 0;
}

