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
        // Child process performs binary search
        int target = 23;
        int low = 0, high = n - 1, found = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] == target) {
                found = mid;
                break;
            } else if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        printf("[Child PID: %d] Binary Searching for %d in sorted array...\n", getpid(), target);
        if (found != -1) {
            printf("[Child] Element %d found at index %d!\n", target, found);
        } else {
            printf("[Child] Element %d not found.\n", target);
        }
        exit(0);
    } else {
        wait(NULL);
        printf("[Parent] Child search operation completed.\n");
    }

    return 0;
}
