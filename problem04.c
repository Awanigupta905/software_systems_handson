#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    // Open an existing file in read-write mode
    fd = open("existing.txt", O_RDWR);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File opened successfully in read-write mode.\n");
    printf("File Descriptor: %d\n", fd);

    close(fd);

    // Try O_CREAT | O_EXCL
    fd = open("existing.txt", O_RDWR | O_CREAT | O_EXCL, 0644);

    if (fd == -1) {
        perror("open with O_EXCL");
    } else {
        printf("File created successfully using O_EXCL.\n");
        close(fd);
    }

    return 0;
}


