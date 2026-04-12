/*
 * Slip 3 - Q2 Option A: Write a C program to display Bus Topology.
 *
 * Compile: gcc Slip_03_Q2_OptionA.c -o bus_topology
 * Run: ./bus_topology
 */

#include <stdio.h>

int main(void) {
    printf("Bus Topology\n");
    printf("============\n\n");
    printf("Nodes connected to a shared bus:\n");
    printf("PC1  <-->\n");
    printf("PC2  <-->  Main Bus  <-->  PC3\n");
    printf("PC4  <-->\n\n");
    printf("All nodes share the same communication medium.\n");
    printf("If one node sends data, it is visible to all nodes.\n");

    return 0;
}
