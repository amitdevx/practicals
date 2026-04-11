/*
 * Slip 19 - Q2 Option B: Mesh Topology Simulation
 * 
 * Simulates 4 PCs in Mesh topology with IP configuration.
 * 
 * Compile: gcc Slip_19_Q2_OptionB.c -o mesh_sim
 * Run: ./mesh_sim
 */

#include <stdio.h>
#include <string.h>

int main() {
    printf("Mesh Topology Simulation\n");
    printf("========================\n\n");
    
    printf("Network Diagram:\n");
    printf("    PC1 --- PC2\n");
    printf("    /|      /|\n");
    printf("   / |     / |\n");
    printf("  PC3 --- PC4\n");
    printf("(All nodes interconnected)\n\n");
    
    typedef struct {
        char name[10];
        char ip[20];
    } Node;
    
    Node nodes[4];
    strcpy(nodes[0].name, "PC1");
    strcpy(nodes[0].ip, "172.16.1.1");
    strcpy(nodes[1].name, "PC2");
    strcpy(nodes[1].ip, "172.16.1.2");
    strcpy(nodes[2].name, "PC3");
    strcpy(nodes[2].ip, "172.16.1.3");
    strcpy(nodes[3].name, "PC4");
    strcpy(nodes[3].ip, "172.16.1.4");
    
    printf("Node Configuration:\n");
    printf("──────────────────────────────\n");
    printf("Node | IP Address      | Mask\n");
    printf("──────────────────────────────\n");
    
    for (int i = 0; i < 4; i++) {
        printf("%-4s | %-15s | /24\n", nodes[i].name, nodes[i].ip);
    }
    
    printf("\nConnectivity (Ping Test):\n");
    printf("PC1 -> PC2: Success\n");
    printf("PC1 -> PC3: Success\n");
    printf("PC1 -> PC4: Success\n");
    printf("PC2 -> PC3: Success\n");
    printf("PC2 -> PC4: Success\n");
    printf("PC3 -> PC4: Success\n");
    printf("All nodes fully connected!\n");
    
    return 0;
}
