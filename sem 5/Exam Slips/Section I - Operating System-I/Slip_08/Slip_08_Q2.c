#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        int old_nice = getpriority(PRIO_PROCESS, 0);
        printf("[Child] Initial Nice Value: %d\n", old_nice);

        // Assign nice value: higher priority
        int new_nice = nice(-5);
        printf("[Child] After nice(-5), Updated Nice Value: %d\n", new_nice);

        printf("[Child] Doing task and finishing...\n");
        exit(0);
    } else {
        // Parent process
        int p_nice = getpriority(PRIO_PROCESS, 0);
        printf("[Parent] Parent Nice Value: %d\n", p_nice);
        wait(NULL);
        printf("[Parent] Child execution complete.\n");
    }

    return 0;
}
