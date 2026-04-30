/*
 * Slip 12 - Q2 Option A: Write a C program to display a Star Topology.
 *
 * Compile: gcc Slip_12_Q2_OptionA.c -o star_topology
 * Run: ./star_topology
 */

#include <stdio.h>

int main(void) {
    printf("Star Topology\n");
    printf("=============\n\n");
    printf("                [Switch 2960]\n");
    printf("              /   |   |   \\\n");
    printf("            PC1  PC2  PC3  PC4  PC5\n");

    return 0;
}
