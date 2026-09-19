#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Executing hello program...\n");

    execl("./hello", "hello", (char *)NULL);

    // This executes only if execl() fails
    perror("execl");
    return 1;
}

