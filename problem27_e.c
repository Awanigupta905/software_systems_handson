#include <stdio.h>
#include <unistd.h>

int main()
{
    char *args[] = {"ls", "-Rl", NULL};

    printf("Executing ls -Rl using execvp()...\n");

    execvp("ls", args);

    perror("execvp");
    return 1;
}

