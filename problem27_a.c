#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Executing ls -Rl using execl()...\n");

    execl("/bin/ls", "ls", "-Rl", (char *)NULL);

    perror("execl");
    return 1;
}


