#include <stdio.h>
#include <unistd.h>

int main() {
    if (symlink("original.txt", "softlink_sys.txt") == -1) {
        perror("symlink");
        return 1;
    }

    printf("Soft link created successfully.\n");

    return 0;
}

