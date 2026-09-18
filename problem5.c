#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd[5];

    fd[0] = open("file1.txt", O_CREAT | O_RDWR, 0644);
    fd[1] = open("file2.txt", O_CREAT | O_RDWR, 0644);
    fd[2] = open("file3.txt", O_CREAT | O_RDWR, 0644);
    fd[3] = open("file4.txt", O_CREAT | O_RDWR, 0644);
    fd[4] = open("file5.txt", O_CREAT | O_RDWR, 0644);

    for (int i = 0; i < 5; i++) {
        if (fd[i] == -1) {
            perror("open");
            return 1;
        }
    }

    printf("Five files created successfully.\n");
    printf("Process ID: %d\n", getpid());

    while (1) {
        sleep(5);
    }

    return 0;
}



