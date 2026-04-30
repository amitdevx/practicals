/*
 * Slip 13 - Q2 Option A: Write a program to displays a Hybrid Topology.
 *
 * Compile: gcc Slip_13_Q2_OptionA.c -o hybrid_topology
 * Run: ./hybrid_topology
 */

#include <stdio.h>

int main(void) {
    printf("Hybrid Topology\n");
    printf("===============\n\n");
    printf("Star Network 1: PC1, PC2, PC3, PC4 -> Switch1\n");
    printf("Star Network 2: PC5, PC6, PC7, PC8 -> Switch2\n");
    printf("Connect Switch1 <-> Switch2\n\n");
    printf("This combines multiple topology types into one network.\n");

    return 0;
}
