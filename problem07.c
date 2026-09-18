#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd1, fd2;
    char buffer[1024];
    int n;

    // Open file1 for reading
    fd1 = open("file1", O_RDONLY);

    if (fd1 == -1) {
        perror("file1");
        return 1;
    }

    // Create file2 for writing
    fd2 = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd2 == -1) {
        perror("file2");
        close(fd1);
        return 1;
    }

    // Read from file1 and write to file2
    while ((n = read(fd1, buffer, sizeof(buffer))) > 0) {
        write(fd2, buffer, n);
    }

    printf("File copied successfully.\n");

    close(fd1);
    close(fd2);

    return 0;
}


