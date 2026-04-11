/*
 * Slip 2 - Q2 Option A: Display Bus Topology
 * 
 * Displays bus topology structure.
 * 
 * Compile: gcc Slip_02_Q2_OptionA.c -o bus_topology
 * Run: ./bus_topology
 */

#include <stdio.h>

int main() {
    printf("Bus Topology\n");
    printf("============\n\n");
    printf("PC1 ──── PC2 ──── PC3 ──── PC4\n");
    printf("(Single shared cable/backbone)\n\n");
    
    printf("Advantages:\n");
    printf("- Simple to install\n");
    printf("- Low cost\n");
    printf("- Easy to understand\n\n");
    
    printf("Disadvantages:\n");
    printf("- Cable failure affects all\n");
    printf("- Difficult to troubleshoot\n");
    printf("- Limited scalability\n");
    
    return 0;
}
