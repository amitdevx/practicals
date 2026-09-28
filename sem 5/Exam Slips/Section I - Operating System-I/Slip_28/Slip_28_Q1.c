#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int req[] = {82, 170, 43, 140, 24, 16, 190, 65};
    int n = sizeof(req) / sizeof(req[0]);
    int head = 50;
    int total_blocks = 200;

    // Sort requests
    qsort(req, n, sizeof(int), compare);

    printf("SCAN Disk Scheduling Simulation (Direction: Left)\n");
    printf("Total Disk Blocks: %d\n", total_blocks);
    printf("Starting Head Position: %d\n", head);

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
