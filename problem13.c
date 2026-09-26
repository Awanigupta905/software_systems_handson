#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>


int main(void) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    struct timeval tv = {10, 0};
    int ret = select(1, &readfds, NULL, NULL, &tv);

    if(ret > 0) printf("Data is available on stdin\n");
    else printf("Timeout, on data received.");

    return 0;
}

