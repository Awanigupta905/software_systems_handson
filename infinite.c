#include <stdio.h>
#include <unistd.h>

int main() {
    while (1) {
        printf("Process is running... PID = %d\n", getpid());
        sleep(5);
    }

    return 0;
}

