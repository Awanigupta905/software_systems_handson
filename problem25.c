#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pids[3];

    for (int i = 0; i < 3; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            printf("Child %d exiting\n", getpid());
            _exit(0);
        }
    }

    waitpid(pids[1], NULL, 0);
    printf("Waited for specific child %d\n", pids[1]);

    return 0;
}

