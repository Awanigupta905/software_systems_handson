#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int hour, minute;
    time_t now;
    struct tm *current_time;
    int target_seconds;
    int current_seconds;
    int wait_seconds;

    if (argc != 2)
    {
        printf("Usage: %s HH:MM\n", argv[0]);
        return 1;
    }

    // Read the time given by the user
    if (sscanf(argv[1], "%d:%d", &hour, &minute) != 2)
    {
        printf("Invalid time format. Use HH:MM\n");
        return 1;
    }

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
    {
        printf("Invalid time.\n");
        return 1;
    }

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        // Parent exits
        printf("Daemon started. Parent process exiting.\n");
        printf("Run time: %02d:%02d\n", hour, minute);
        printf("Daemon PID: %d\n", pid);
        return 0;
    }

    // Create new session
    if (setsid() == -1)
    {
        perror("setsid");
        exit(1);
    }

    // Change working directory
    chdir("/");

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Get current time
    time(&now);
    current_time = localtime(&now);

    current_seconds =
        current_time->tm_hour * 3600 +
        current_time->tm_min * 60 +
        current_time->tm_sec;

    target_seconds = hour * 3600 + minute * 60;

    wait_seconds = target_seconds - current_seconds;

    // If the specified time has already passed,
    // schedule it for the next day.
    if (wait_seconds <= 0)
    {
        wait_seconds += 24 * 60 * 60;
    }

    sleep(wait_seconds);

    // Execute the script
    execl("/bin/bash", "bash", "/home/awani/ss_new/script30.sh", (char *)NULL);

    exit(0);
}


