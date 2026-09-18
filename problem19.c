#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

static inline uint64_t read_timestamp_counter()
{
    uint64_t counter;

    asm volatile("mrs %0, cntvct_el0" : "=r"(counter));

    return counter;
}

int main()
{
    uint64_t start, end;
    pid_t pid;

    start = read_timestamp_counter();

    pid = getpid();

    end = read_timestamp_counter();

    printf("Process ID: %d\n", pid);
    printf("Time taken by getpid(): %llu timestamp counter ticks\n",
           (unsigned long long)(end - start));

    return 0;
}

