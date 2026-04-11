/*
 * Slip 17 - Q2 Option B: Bus Topology Simulation
 * 
 * Simulates 4 PCs in Bus topology with IP configuration.
 * 
 * Compile: gcc Slip_17_Q2_OptionB.c -o bus_topology
 * Run: ./bus_topology
 */

#include <stdio.h>
#include <string.h>

int main() {
    printf("Bus Topology Simulation\n");
    printf("=======================\n\n");
    
    printf("Network Structure:\n");
    printf("PC1 ---- PC2 ---- PC3 ---- PC4\n");
    printf("(Single shared cable/backbone)\n\n");
    
    typedef struct {
        char name[10];
        char ip[20];
        char mask[20];
    } PC;
    
    PC nodes[4];
    strcpy(nodes[0].name, "PC1");
    strcpy(nodes[0].ip, "192.168.1.1");
    strcpy(nodes[0].mask, "255.255.255.0");
    
    strcpy(nodes[1].name, "PC2");
    strcpy(nodes[1].ip, "192.168.1.2");
    strcpy(nodes[1].mask, "255.255.255.0");
    
    strcpy(nodes[2].name, "PC3");
    strcpy(nodes[2].ip, "192.168.1.3");
    strcpy(nodes[2].mask, "255.255.255.0");
    
    strcpy(nodes[3].name, "PC4");
    strcpy(nodes[3].ip, "192.168.1.4");
    strcpy(nodes[3].mask, "255.255.255.0");
    
    printf("IP Configuration:\n");
    printf("─────────────────────────────────────\n");
    printf("Name | IP              | Subnet Mask\n");
    printf("─────────────────────────────────────\n");
    
    for (int i = 0; i < 4; i++) {
        printf("%-4s | %-15s | %s\n",
            nodes[i].name, nodes[i].ip, nodes[i].mask);
    }
    
    printf("\nConnectivity Test (Ping):\n");
    printf("PC1 -> PC2: Success\n");
    printf("PC1 -> PC3: Success\n");
    printf("PC1 -> PC4: Success\n");
    printf("PC2 -> PC4: Success\n");
    printf("(All nodes reachable via bus)\n");
    
    return 0;
}
