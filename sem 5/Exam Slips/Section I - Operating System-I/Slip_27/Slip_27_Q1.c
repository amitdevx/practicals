#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int n, head, total_blocks;
    printf("Enter total number of disk blocks: ");
    if (scanf("%d", &total_blocks) != 1) total_blocks = 200;
    
    printf("Enter number of requests: ");
    if (scanf("%d", &n) != 1 || n <= 0) n = 7;
    
    int req[50];
    printf("Enter disk request string: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &req[i]) != 1) {
            int default_req[] = {30, 10, 60, 95, 120, 150, 175};
            for (int j = 0; j < 7; j++) req[j] = default_req[j];
            n = 7;
            break;
        }
    }
    
    printf("Enter starting head position: ");
    if (scanf("%d", &head) != 1) head = 50;

    bool visited[50] = {false};

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
