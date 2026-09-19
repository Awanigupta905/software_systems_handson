#include <stdio.h>
#include <sched.h>

int main()
{
    int min_priority;
    int max_priority;

    // Get minimum real-time priority
    min_priority = sched_get_priority_min(SCHED_FIFO);

    if (min_priority == -1)
    {
        perror("sched_get_priority_min");
        return 1;
    }

    // Get maximum real-time priority
    max_priority = sched_get_priority_max(SCHED_FIFO);

    if (max_priority == -1)
    {
        perror("sched_get_priority_max");
        return 1;
    }

    printf("Real-time scheduling policy: SCHED_FIFO\n");
    printf("Minimum real-time priority: %d\n", min_priority);
    printf("Maximum real-time priority: %d\n", max_priority);

    return 0;
}

