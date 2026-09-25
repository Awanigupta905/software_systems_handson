#include <stdio.h>
#include <sched.h>

int main() {
    printf("Current policy: %d\n", sched_getscheduler(0));

    struct sched_param param;
    param.sched_priority = 1;
    sched_setscheduler(0, SCHED_RR, &param);

    printf("New policy: %d\n", sched_getscheduler(0));

    return 0;
}

