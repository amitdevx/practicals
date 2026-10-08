#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, head, total_blocks;
    printf("Enter total number of disk blocks: ");
    scanf("%d", &total_blocks);
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int req[n];
    printf("Enter disk request string: ");
    for(int i=0; i<n; i++) {
        scanf("%d", &req[i]);
    }
    printf("Enter current head position: ");
    scanf("%d", &head);

    // Sort requests
    qsort(req, n, sizeof(int), compare);

    printf("SCAN Disk Scheduling Simulation (Direction: Left)\n");

    int total_head_movements = 0;
    int current_head = head;

    printf("\nOrder of Request Service:\n%d", head);

    // Direction: Left means service downwards towards 0, then reverse
    int idx = 0;
    while (idx < n && req[idx] < head) idx++;

    for (int i = idx - 1; i >= 0; i--) {
        total_head_movements += abs(req[i] - current_head);
        current_head = req[i];
        printf(" -> %d", current_head);
    }
    // Head reaches cylinder 0
    total_head_movements += abs(0 - current_head);
    current_head = 0;
    printf(" -> 0");

    // Reverse direction to the right
    for (int i = idx; i < n; i++) {
        total_head_movements += abs(req[i] - current_head);
        current_head = req[i];
        printf(" -> %d", current_head);
    }

    printf("\n\nTotal Head Movements: %d cylinders\n", total_head_movements);
    return 0;
}
