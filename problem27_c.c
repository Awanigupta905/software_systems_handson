#include <stdio.h>
#include <unistd.h>

int main()
{
    char *envp[] = {NULL};

    printf("Executing ls -Rl using execle()...\n");

    execle("/bin/ls", "ls", "-Rl", (char *)NULL, envp);

    perror("execle");
    return 1;
}

