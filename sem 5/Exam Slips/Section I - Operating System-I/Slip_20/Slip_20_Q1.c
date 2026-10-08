#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int total_blocks, n, head;
    printf("Enter total number of disk blocks: ");
    if (scanf("%d", &total_blocks) != 1) return 1;

    printf("Enter number of requests: ");
    if (scanf("%d", &n) != 1) return 1;

    int *req = malloc(n * sizeof(int));
    printf("Enter disk request string: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &req[i]) != 1) return 1;
    }

    printf("Enter current head position: ");
    if (scanf("%d", &head) != 1) return 1;

    qsort(req, n, sizeof(int), compare);

    printf("\nLOOK Disk Scheduling Simulation (Direction: Right)\n");
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
    free(req);
    return 0;
}
