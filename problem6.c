#include <unistd.h>

int main() {
    char buffer[100];
    int n;

    // Read input from STDIN
    n = read(0, buffer, sizeof(buffer));

    // Display input on STDOUT
    write(1, buffer, n);

    return 0;
}

