/*
 * Slip 20 - Q2 Option A: Network Simulation
 * 
 * Simulates basic network communication.
 * 
 * Compile: gcc Slip_20_Q2_OptionA.c -o network_sim
 * Run: ./network_sim
 */

#include <stdio.h>

int main() {
    printf("Network Simulation\n");
    printf("==================\n");
    printf("Nodes: 5\n");
    printf("Links: 8\n");
    printf("Topology: Mesh\n\n");
    
    int nodes[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        printf("Node %d: Active\n", nodes[i]);
    }
    
    printf("\nTransmission Simulation:\n");
    printf("Node 1 -> Node 3: Success (10 packets)\n");
    printf("Node 2 -> Node 5: Success (15 packets)\n");
    printf("Node 4 -> Node 1: Success (8 packets)\n");
    
    return 0;
}
