#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        sleep(5);
        printf("Child pid: %d, parent pid: %d\n", getpid(), getppid());
    } else {
        printf("Parent exiting\n");
        _exit(0);
    }

    return 0;
}

