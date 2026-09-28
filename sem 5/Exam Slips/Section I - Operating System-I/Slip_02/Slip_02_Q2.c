#include <stdio.h>
#include <stdlib.h>

int main() {
    int default_req[] = {55, 58, 39, 18, 90, 160, 150, 38, 184};
    int n = sizeof(default_req) / sizeof(default_req[0]);
    int head = 50;
    int total_blocks = 200;

    printf("FCFS Disk Scheduling Simulation\n");
    printf("Total Disk Blocks: %d\n", total_blocks);
    printf("Starting Head Position: %d\n", head);

    int total_head_movements = 0;
    int current_head = head;

    printf("\nOrder of Request Service:\n%d", head);
    for (int i = 0; i < n; i++) {
        int movement = abs(default_req[i] - current_head);
        total_head_movements += movement;
        current_head = default_req[i];
        printf(" -> %d", current_head);
    }

    printf("\n\nTotal Head Movements: %d cylinders\n", total_head_movements);
    return 0;
}
