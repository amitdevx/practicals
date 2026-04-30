/*
 * Slip 15 - Q2 Option B: Write a program to displays a Mesh Topology.
 *
 * Compile: gcc Slip_15_Q2_OptionB.c -o mesh_topology
 * Run: ./mesh_topology
 */

#include <stdio.h>

int main(void) {
    printf("Mesh Topology\n");
    printf("=============\n\n");
    printf("PC1 <-> PC2 <-> PC3 <-> PC4\n");
    printf("|  \\        |        /  |\n");
    printf("+---+-------+-------+---+\n");

    return 0;
}
