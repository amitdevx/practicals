/*
 * Slip 5 - Q2 Option A: Write a C program to display a Ring Topology.
 *
 * Compile: gcc Slip_05_Q2_OptionA.c -o ring_topology
 * Run: ./ring_topology
 */

#include <stdio.h>

int main(void) {
    printf("Ring Topology\n");
    printf("=============\n\n");
    printf("Node 1 -> Node 2 -> Node 3 -> Node 4 -> Node 1\n\n");
    printf("Each node has exactly two neighbors in the ring.\n");
    printf("If one link fails, the ring communication is affected.\n");

    return 0;
}
