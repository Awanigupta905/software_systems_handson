#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    int flags;

    // Open the file in read-write mode
    fd = open("file12.txt", O_RDWR | O_CREAT, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Get the file status flags
    flags = fcntl(fd, F_GETFL);

    if (flags == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    // Check the opening mode
    if ((flags & O_ACCMODE) == O_RDONLY) {
        printf("File is opened in READ ONLY mode.\n");
    }
    else if ((flags & O_ACCMODE) == O_WRONLY) {
        printf("File is opened in WRITE ONLY mode.\n");
    }
    else if ((flags & O_ACCMODE) == O_RDWR) {
        printf("File is opened in READ-WRITE mode.\n");
    }

    close(fd);

    return 0;
}

