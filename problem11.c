#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, fd_dup, fd_dup2, fd_fcntl;

    // Open file in append mode
    fd = open("file11.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // ------------------------------------------------
    // a. Duplicate using dup()
    // ------------------------------------------------
    fd_dup = dup(fd);

    if (fd_dup == -1) {
        perror("dup");
        close(fd);
        return 1;
    }

    write(fd, "Written using original fd\n", 26);
    write(fd_dup, "Written using dup fd\n", 21);

    printf("Original FD: %d\n", fd);
    printf("dup() FD   : %d\n", fd_dup);

    close(fd_dup);


    // ------------------------------------------------
    // b. Duplicate using dup2()
    // ------------------------------------------------
    fd_dup2 = dup2(fd, 10);

    if (fd_dup2 == -1) {
        perror("dup2");
        close(fd);
        return 1;
    }

    write(fd, "Written using original fd again\n", 33);
    write(fd_dup2, "Written using dup2 fd\n", 22);

    printf("dup2() FD  : %d\n", fd_dup2);

    close(fd_dup2);


    // ------------------------------------------------
    // c. Duplicate using fcntl()
    // ------------------------------------------------
    fd_fcntl = fcntl(fd, F_DUPFD, 10);

    if (fd_fcntl == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    write(fd, "Written using original fd again\n", 33);
    write(fd_fcntl, "Written using fcntl fd\n", 24);

    printf("fcntl() FD : %d\n", fd_fcntl);

    close(fd_fcntl);
    close(fd);

    return 0;
}

