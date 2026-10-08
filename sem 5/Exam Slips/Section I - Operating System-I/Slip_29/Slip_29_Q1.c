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
    int n, target;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter target element to search: ");
    scanf("%d", &target);

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
        args[0] = "./Slip_29_Q1_binary_search";
        char target_str[20];
        sprintf(target_str, "%d", target);
        args[1] = target_str;

        for (int i = 0; i < n; i++) {
            args[i + 2] = malloc(20);
            sprintf(args[i + 2], "%d", arr[i]);
        }
        args[n + 2] = NULL;
        
        char *envp[] = {NULL};
        execve(args[0], args, envp);
        perror("execve");
        exit(1);
    } else {
        wait(NULL);
        printf("[Parent] Child search operation completed.\n");
    }

    return 0;
}
