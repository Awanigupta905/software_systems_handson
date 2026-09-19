#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Executing ls -Rl using execlp()...\n");

    execlp("ls", "ls", "-Rl", (char *)NULL);

    perror("execlp");
    return 1;
}

