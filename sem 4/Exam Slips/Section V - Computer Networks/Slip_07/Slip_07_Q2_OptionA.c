/*
 * Slip 7 - Q2 Option A: Write a program to displays a Mesh Topology.
 *
 * Compile: gcc Slip_07_Q2_OptionA.c -o mesh_topology
 * Run: ./mesh_topology
 */

#include <stdio.h>

typedef struct {
    const char *name;
    const char *ip;
    const char *mask;
} PC;

int main(void) {
    PC pcs[4] = {
        {"PC1", "192.168.1.1", "255.255.255.0"},
        {"PC2", "192.168.1.2", "255.255.255.0"},
        {"PC3", "192.168.1.3", "255.255.255.0"},
        {"PC4", "192.168.1.4", "255.255.255.0"}
    };

    printf("Mesh Topology\n");
    printf("=============\n\n");
    printf("PC1 <-> PC2 <-> PC3 <-> PC4\n");
    printf("|  \\        |        /  |\n");
    printf("+---+-------+-------+---+\n\n");

    printf("IP Configuration:\n");
    printf("----------------------------------------\n");
    printf("Device   IP Address      Subnet Mask\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < 4; i++) {
        printf("%-6s   %-14s %s\n", pcs[i].name, pcs[i].ip, pcs[i].mask);
    }

    return 0;
}
