/*
 * Slip 14 - Q2 Option A: Mesh Topology Display
 * 
 * Displays mesh topology with all nodes connected to all nodes.
 * 
 * Compile: gcc Slip_14_Q2_OptionA.c -o mesh_topology
 * Run: ./mesh_topology
 */

#include <stdio.h>

int main() {
    printf("Mesh Topology\n");
    printf("=============\n\n");
    printf("Full Mesh Configuration (4 nodes)\n\n");
    
    printf("         PC1 --- PC2\n");
    printf("        / |   X   | \\\n");
    printf("       /  | /   \\ |  \\\n");
    printf("      PC4 |/     \\| PC3\n\n");
    
    printf("Node Connections:\n");
    int nodes = 4;
    for (int i = 1; i <= nodes; i++) {
        for (int j = 1; j <= nodes; j++) {
            if (i != j) {
                printf("PC%d <-> PC%d\n", i, j);
            }
        }
    }
    
    printf("\nAdvantages:\n");
    printf("- Fully redundant\n");
    printf("- High reliability\n");
    printf("- Direct communication\n");
    printf("- No congestion\n\n");
    
    printf("Disadvantages:\n");
    printf("- Expensive (many cables)\n");
    printf("- Complex to maintain\n");
    printf("- Not scalable\n");
    
    return 0;
}
