#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    int key = atoi(argv[1]);
    int n = argc - 2;
    int a[20];
    printf("Child received sorted array: ");
    for (int i = 0; i < n; i++) {
        a[i] = atoi(argv[i + 2]);
        printf("%d ", a[i]);
    }
    printf("\n");
    int low = 0, high = n - 1, found = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == key) {
            found = mid;
            break;
        } else if (a[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    if (found != -1) printf("Element %d found at position %d\n", key, found + 1);
    else printf("Element %d not found\n", key);
    return 0;
}
