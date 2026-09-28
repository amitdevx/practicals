#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("[Child] PID: %d, Initial Parent PID: %d\n", getpid(), getppid());
        printf("[Child] Sleeping for 4 seconds to become orphan...\n");
        sleep(4);
        printf("[Child] Woke up! Current Parent PID: %d (Adopted by systemd/init)\n", getppid());
        printf("[Child] Exiting normally.\n");
    } else {
        // Parent process
        printf("[Parent] PID: %d, Child PID: %d\n", getpid(), pid);
        printf("[Parent] Terminating immediately without waiting for child.\n");
        exit(0);
    }

    return 0;
}
