/*
 * Slip 4 - Q2 Option A: Ring Topology Display
 * 
 * Displays ring topology structure and nodes.
 * 
 * Compile: gcc Slip_04_Q2_OptionA.c -o ring_topology
 * Run: ./ring_topology
 */

#include <stdio.h>

int main() {
    printf("Ring Topology\n");
    printf("=============\n");
    printf("Structure: Nodes connected in a circle\n");
    printf("Node 1 -> Node 2 -> Node 3 -> Node 4 -> Node 1\n\n");
    
    printf("Ring Configuration:\n");
    for (int i = 1; i <= 4; i++) {
        int next = (i % 4) + 1;
        printf("Node %d -> Node %d\n", i, next);
    }
    
    printf("\nAdvantages:\n");
    printf("- Fair data transmission\n");
    printf("- No collisions\n");
    printf("- Good for large networks\n");
    
    printf("\nDisadvantages:\n");
    printf("- One node failure breaks ring\n");
    printf("- Complex to configure\n");
    
    return 0;
}
