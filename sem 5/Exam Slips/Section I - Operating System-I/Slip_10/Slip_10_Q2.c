#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int req[] = {86, 147, 91, 177, 45, 12, 130};
    int n = sizeof(req) / sizeof(req[0]);
    int head = 60;

    qsort(req, n, sizeof(int), compare);

    printf("LOOK Disk Scheduling Simulation (Direction: Right)\n");
    printf("Starting Head Position: %d\n", head);

    int total_head_movements = 0;
    int current_head = head;

    printf("\nOrder of Request Service:\n%d", head);

    int idx = 0;
    while (idx < n && req[idx] < head) idx++;

    // Service to the right first
    for (int i = idx; i < n; i++) {
        total_head_movements += abs(req[i] - current_head);
        current_head = req[i];
        printf(" -> %d", current_head);
    }

    // Then reverse to the left (without going to edge 0)
    for (int i = idx - 1; i >= 0; i--) {
        total_head_movements += abs(req[i] - current_head);
        current_head = req[i];
        printf(" -> %d", current_head);
    }

    printf("\n\nTotal Head Movements: %d cylinders\n", total_head_movements);
    return 0;
}
