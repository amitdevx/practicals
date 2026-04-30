/*
 * Slip 20 - Q2 Option A: Mesh Topology Representation
 *
 * As per slip practical: 4 PCs in mesh with:
 * PC1 172.16.1.1/16, PC2 172.16.1.2/16,
 * PC3 172.16.1.3/16, PC4 172.16.1.4/16
 *
 * Compile: gcc Slip_20_Q2_OptionA.c -o mesh_topology
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
        {"PC1", "172.16.1.1", "255.255.0.0"},
        {"PC2", "172.16.1.2", "255.255.0.0"},
        {"PC3", "172.16.1.3", "255.255.0.0"},
        {"PC4", "172.16.1.4", "255.255.0.0"}
    };

    printf("Mesh Topology Representation (4 PCs)\n");
    printf("====================================\n\n");

    printf("All-to-all logical links:\n");
    printf("PC1 <-> PC2, PC1 <-> PC3, PC1 <-> PC4\n");
    printf("PC2 <-> PC3, PC2 <-> PC4\n");
    printf("PC3 <-> PC4\n\n");

    printf("IP Configuration:\n");
    printf("----------------------------------------\n");
    printf("Device   IP Address      Subnet Mask\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < 4; i++) {
        printf("%-6s   %-14s %s\n", pcs[i].name, pcs[i].ip, pcs[i].mask);
    }

    printf("\nConnectivity status (simulated):\n");
    printf("All four nodes can communicate with each other.\n");

    return 0;
}
