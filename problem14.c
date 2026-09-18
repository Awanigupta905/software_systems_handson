#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct stat file;

    // Check command-line argument
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get file information
    if (lstat(argv[1], &file) == -1) {
        perror("lstat");
        return 1;
    }

    // Identify file type
    if (S_ISREG(file.st_mode)) {
        printf("%s is a Regular File.\n", argv[1]);
    }
    else if (S_ISDIR(file.st_mode)) {
        printf("%s is a Directory.\n", argv[1]);
    }
    else if (S_ISLNK(file.st_mode)) {
        printf("%s is a Symbolic Link.\n", argv[1]);
    }
    else if (S_ISFIFO(file.st_mode)) {
        printf("%s is a FIFO (Named Pipe).\n", argv[1]);
    }
    else if (S_ISSOCK(file.st_mode)) {
        printf("%s is a Socket.\n", argv[1]);
    }
    else if (S_ISCHR(file.st_mode)) {
        printf("%s is a Character Device.\n", argv[1]);
    }
    else if (S_ISBLK(file.st_mode)) {
        printf("%s is a Block Device.\n", argv[1]);
    }
    else {
        printf("%s is of an Unknown File Type.\n", argv[1]);
    }

    return 0;
}

