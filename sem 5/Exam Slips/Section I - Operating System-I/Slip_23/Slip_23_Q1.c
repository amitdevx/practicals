#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubble_sort(int arr[], int n) {
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

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n;
    printf("Enter number of integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) n = 5;

    int arr[50];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) arr[i] = (i + 1) * 3;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child sorts using Insertion Sort
        printf("\n[Child PID: %d] Sorting using Insertion Sort...\n", getpid());
        insertion_sort(arr, n);
        printf("[Child] Sorted Array: ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
        exit(0);
    } else {
        // Parent sorts using Bubble Sort and waits
        wait(NULL);
        printf("\n[Parent PID: %d] Child finished. Sorting using Bubble Sort...\n", getpid());
        bubble_sort(arr, n);
        printf("[Parent] Sorted Array: ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
    }

    return 0;
}
