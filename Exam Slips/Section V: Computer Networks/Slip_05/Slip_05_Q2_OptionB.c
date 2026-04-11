/*
 * Slip 5 - Q2 Option B: Star Topology Display
 * 
 * Displays star topology with central switch.
 * 
 * Compile: gcc Slip_05_Q2_OptionB.c -o star_topology
 * Run: ./star_topology
 */

#include <stdio.h>

int main() {
    printf("Star Topology\n");
    printf("=============\n\n");
    printf("                    SWITCH (Center)\n");
    printf("                         |\n");
    printf("          PC1 -------- PC2 -------- PC3\n");
    printf("                         |\n");
    printf("                      PC4\n\n");
    
    printf("Configuration:\n");
    for (int i = 1; i <= 4; i++) {
        printf("PC%d: 192.168.1.%d\n", i, i + 10);
    }
    
    printf("\nAdvantages:\n");
    printf("- Central management\n");
    printf("- Easy to add/remove nodes\n");
    printf("- Good performance\n");
    
    printf("\nDisadvantages:\n");
    printf("- Switch is single point of failure\n");
    printf("- More cable needed\n");
    
    return 0;
}
