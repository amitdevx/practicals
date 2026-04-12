/*
 * Slip 6 - Q2 Option B: Write a program to display Star Topology.
 *
 * Compile: gcc Slip_06_Q2_OptionB.c -o star_topology
 * Run: ./star_topology
 */

#include <stdio.h>

int main(void) {
    printf("Star Topology\n");
    printf("=============\n\n");
    printf("                [Switch 2960]\n");
    printf("              /   |   |   \\\n");
    printf("            PC1  PC2  PC3  PC4  PC5\n\n");
    printf("PC1: 192.168.1.1 / 255.255.255.0\n");
    printf("PC2: 192.168.1.2 / 255.255.255.0\n");
    printf("PC3: 192.168.1.3 / 255.255.255.0\n");
    printf("PC4: 192.168.1.4 / 255.255.255.0\n");
    printf("PC5: 192.168.1.5 / 255.255.255.0\n");

    return 0;
}
