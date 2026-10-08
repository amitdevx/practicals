#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void sort_array(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n = 5;
    int arr[] = {45, 12, 89, 23, 7};
    int target = 23;

    printf("[Parent] Original Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    sort_array(arr, n);
    printf("[Parent] Sorted Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        char *args[n + 3];
        args[0] = "./Slip_24_Q2_child";
        
        for (int i = 0; i < n; i++) {
            args[i + 1] = malloc(10);
            sprintf(args[i + 1], "%d", arr[i]);
        }
        
        args[n + 1] = malloc(10);
        sprintf(args[n + 1], "%d", target);
        
        args[n + 2] = NULL;
        
        execve(args[0], args, NULL);
        perror("execve failed");
        exit(1);
    } else {
        wait(NULL);
        printf("[Parent] Child search operation completed.\n");
    }

    return 0;
}
