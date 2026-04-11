/*
 * Slip 20 - Q2 Option B: Topology Simulation
 * 
 * Displays various network topologies.
 * 
 * Compile: gcc Slip_20_Q2_OptionB.c -o topology
 * Run: ./topology
 */

#include <stdio.h>

int main() {
    printf("Network Topologies\n");
    printf("==================\n\n");
    
    printf("1. Star Topology:\n");
    printf("   Switch at center, nodes connected radially\n\n");
    
    printf("2. Ring Topology:\n");
    printf("   Nodes connected in circle\n");
    printf("   Node 1 - Node 2 - Node 3 - Node 1\n\n");
    
    printf("3. Mesh Topology:\n");
    printf("   All nodes connected to all other nodes\n");
    printf("   Full connectivity, higher cost\n\n");
    
    printf("4. Bus Topology:\n");
    printf("   All nodes share single communication line\n");
    printf("   Simple, vulnerable\n");
    
    return 0;
}
