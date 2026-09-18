#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    struct stat file;

    if (stat("input.txt", &file) == -1) {
        perror("stat");
        return 1;
    }

    printf("Inode number       : %ld\n", file.st_ino);
    printf("Number of links    : %ld\n", file.st_nlink);
    printf("UID                : %d\n", file.st_uid);
    printf("GID                : %d\n", file.st_gid);
    printf("Size               : %ld bytes\n", file.st_size);
    printf("Block size         : %ld bytes\n", file.st_blksize);
    printf("Number of blocks   : %ld\n", file.st_blocks);

    printf("Last access        : %s", ctime(&file.st_atime));
    printf("Last modification  : %s", ctime(&file.st_mtime));
    printf("Last change        : %s", ctime(&file.st_ctime));

    return 0;
}

