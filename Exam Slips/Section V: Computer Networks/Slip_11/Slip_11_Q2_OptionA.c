/*
 * Slip 11 - Q2 Option A: Display Star Topology
 * 
 * Displays star topology structure.
 * 
 * Compile: gcc Slip_11_Q2_OptionA.c -o star_topology
 * Run: ./star_topology
 */

#include <stdio.h>

int main() {
    printf("Star Topology\n");
    printf("=============\n\n");
    printf("           Switch\n");
    printf("             |\n");
    printf("    ┌────────┼────────┐\n");
    printf("   PC1      PC2      PC3\n\n");
    
    printf("Advantages:\n");
    printf("- Central management\n");
    printf("- Easy to add nodes\n");
    printf("- Good performance\n\n");
    
    printf("Disadvantages:\n");
    printf("- Switch is single point of failure\n");
    printf("- More cabling required\n");
    
    return 0;
}
