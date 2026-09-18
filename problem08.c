#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char ch;

    fd = open("input.txt", O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    while (read(fd, &ch, 1) > 0) {
        write(STDOUT_FILENO, &ch, 1);

        if (ch == '\n') {
            // End of current line
        }
    }

    close(fd);

    return 0;
}

