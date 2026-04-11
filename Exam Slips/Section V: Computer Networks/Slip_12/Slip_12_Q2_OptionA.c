/*
 * Slip 12 - Q2 Option A: Hybrid Topology Display
 * 
 * Displays hybrid topology (combination of topologies).
 * 
 * Compile: gcc Slip_12_Q2_OptionA.c -o hybrid_topology
 * Run: ./hybrid_topology
 */

#include <stdio.h>

int main() {
    printf("Hybrid Topology\n");
    printf("===============\n\n");
    printf("Combination of multiple topologies\n\n");
    
    printf("Configuration:\n");
    printf("Department 1: Star (3 nodes)\n");
    printf("Department 2: Bus (3 nodes)\n");
    printf("Department 3: Ring (3 nodes)\n");
    printf("Connected via backbone (Main Router)\n\n");
    
    printf("Advantages:\n");
    printf("- Flexibility\n");
    printf("- Scalability\n");
    printf("- Fault isolation\n");
    printf("- Better performance\n\n");
    
    printf("Disadvantages:\n");
    printf("- Complex design\n");
    printf("- Expensive\n");
    printf("- Difficult to manage\n");
    
    return 0;
}
