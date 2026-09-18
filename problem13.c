#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main() {
    fd_set readfds;
    struct timeval timeout;
    int result;

    // Clear the set
    FD_ZERO(&readfds);

    // Add STDIN (file descriptor 0)
    FD_SET(STDIN_FILENO, &readfds);

    // Set timeout to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input for 10 seconds...\n");

    // Wait for STDIN to become ready
    result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (result == -1) {
        perror("select");
    }
    else if (result == 0) {
        printf("No data available within 10 seconds.\n");
    }
    else {
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            printf("Data is available within 10 seconds.\n");
        }
    }

    return 0;
}

