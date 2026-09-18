#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {

    // Create an original file
    FILE *file = fopen("original.txt", "w");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    fprintf(file, "This is the original file.\n");
    fclose(file);

    // 1. Create Soft Link
    if (symlink("original.txt", "softlink.txt") == -1) {
        perror("symlink");
    } else {
        printf("Soft link created successfully.\n");
    }

    // 2. Create Hard Link
    if (link("original.txt", "hardlink.txt") == -1) {
        perror("link");
    } else {
        printf("Hard link created successfully.\n");
    }

    // 3. Create FIFO
    if (mkfifo("myfifo", 0666) == -1) {
        perror("mkfifo");
    } else {
        printf("FIFO created successfully.\n");
    }

    return 0;
}



