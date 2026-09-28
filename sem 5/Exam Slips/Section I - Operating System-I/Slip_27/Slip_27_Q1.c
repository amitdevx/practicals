#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int req[] = {30, 10, 60, 95, 120, 150, 175};
    int n = sizeof(req) / sizeof(req[0]);
    bool visited[50] = {false};
    int head = 50;

    printf("SSTF Disk Scheduling Simulation\n");
    printf("Starting Head Position: %d\n", head);

    int total_head_movements = 0;
    int current_head = head;

    printf("\nOrder of Request Service:\n%d", head);
    for (int count = 0; count < n; count++) {
        int min_dist = 1e9;
        int next_idx = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int dist = abs(req[i] - current_head);
                if (dist < min_dist) {
                    min_dist = dist;
                    next_idx = i;
                }
            }
        }

        visited[next_idx] = true;
        total_head_movements += min_dist;
        current_head = req[next_idx];
        printf(" -> %d", current_head);
    }

    printf("\n\nTotal Head Movements: %d cylinders\n", total_head_movements);
    return 0;
}
