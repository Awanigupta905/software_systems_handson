#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Executing name_program...\n");

    execl("./name_program", "name_program", "Awani", (char *)NULL);

    // This executes only if execl() fails
    perror("execl");
    return 1;
}

