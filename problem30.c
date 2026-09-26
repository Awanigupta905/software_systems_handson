#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main() {
    daemon(0, 0);

    while (1) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        if (t->tm_hour == 12 && t->tm_min == 0)
            system("echo task executed >> lab30.txt");

        sleep(60);
    }

    return 0;
}

