#include <stdio.h>
#include <unistd.h>
#include <sched.h>

void print_policy(int policy)
{
    if (policy == SCHED_OTHER)
    {
        printf("Scheduling Policy: SCHED_OTHER\n");
    }
    else if (policy == SCHED_FIFO)
    {
        printf("Scheduling Policy: SCHED_FIFO\n");
    }
    else if (policy == SCHED_RR)
    {
        printf("Scheduling Policy: SCHED_RR\n");
    }
    else
    {
        printf("Unknown Scheduling Policy\n");
    }
}

int main()
{
    int policy;
    struct sched_param param;

    // Get current scheduling policy
    policy = sched_getscheduler(0);

    if (policy == -1)
    {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Current scheduling policy:\n");
    print_policy(policy);

    // Set priority
    param.sched_priority = sched_get_priority_min(SCHED_FIFO);

    // Change policy to SCHED_FIFO
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1)
    {
        perror("sched_setscheduler SCHED_FIFO");
    }
    else
    {
        printf("\nAfter changing to SCHED_FIFO:\n");

        policy = sched_getscheduler(0);
        print_policy(policy);
    }

    // Set priority for SCHED_RR
    param.sched_priority = sched_get_priority_min(SCHED_RR);

    // Change policy to SCHED_RR
    if (sched_setscheduler(0, SCHED_RR, &param) == -1)
    {
        perror("sched_setscheduler SCHED_RR");
    }
    else
    {
        printf("\nAfter changing to SCHED_RR:\n");

        policy = sched_getscheduler(0);
        print_policy(policy);
    }

    return 0;
}

