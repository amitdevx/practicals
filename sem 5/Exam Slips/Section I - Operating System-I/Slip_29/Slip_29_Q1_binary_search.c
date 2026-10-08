#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    int n = argc - 2;
    int target = atoi(argv[argc - 1]);
    int arr[50];
    printf("[Child PID: %d] Array received: ", getpid());
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
        printf("%d ", arr[i]);
    }
    printf("\n[Child] Binary Searching for %d...\n", target);
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
    if (found != -1) printf("[Child] Element %d found at index %d!\n", target, found);
    else printf("[Child] Element %d not found.\n", target);
    return 0;
}
