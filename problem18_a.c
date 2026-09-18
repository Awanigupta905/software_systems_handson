#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define RECORD_SIZE 50

int main(int argc, char *argv[])
{
    int fd;
    int record_no;
    struct flock lock;
    char buffer[RECORD_SIZE];

    if (argc != 2)
    {
        printf("Usage: %s <record_number>\n", argv[0]);
        return 1;
    }

    record_no = atoi(argv[1]);

    if (record_no < 1 || record_no > 3)
    {
        printf("Record number must be 1, 2 or 3\n");
        return 1;
    }

    fd = open("records.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    /* Calculate the position of the selected record */
    off_t position = (record_no - 1) * RECORD_SIZE;

    /* Set write lock */
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = position;
    lock.l_len = RECORD_SIZE;

    printf("Requesting write lock on record %d...\n", record_no);

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Write lock acquired on record %d.\n", record_no);

    /* Move to the selected record */
    lseek(fd, position, SEEK_SET);

    /* Read the record */
    int n = read(fd, buffer, RECORD_SIZE);

    if (n == -1)
    {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[n] = '\0';

    printf("Old record: %s", buffer);

    /* Modify the record */
    char name[30];
    int id, balance;

    sscanf(buffer, "%d %s %d", &id, name, &balance);

    balance += 500;

    printf("Adding 500 to the balance...\n");

    snprintf(buffer, RECORD_SIZE, "%d %s %d\n",
             id, name, balance);

    /* Write updated record */
    lseek(fd, position, SEEK_SET);

    if (write(fd, buffer, RECORD_SIZE) == -1)
    {
        perror("write");
        close(fd);
        return 1;
    }

    printf("New record: %s", buffer);

    /* Release lock */
    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLK, &lock) == -1)
    {
        perror("unlock");
    }

    printf("Write lock released.\n");

    close(fd);

    return 0;
}

