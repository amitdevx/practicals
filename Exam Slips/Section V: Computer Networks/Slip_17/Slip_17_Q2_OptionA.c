/*
 * Slip 17 - Q2 Option A: Frame Relay Protocol
 * 
 * Displays Frame Relay concepts and parameters.
 * 
 * Compile: gcc Slip_17_Q2_OptionA.c -o frame_relay
 * Run: ./frame_relay
 */

#include <stdio.h>

int main() {
    printf("Frame Relay Protocol\n");
    printf("====================\n");
    printf("Concepts:\n");
    printf("- PVC (Permanent Virtual Circuit)\n");
    printf("- SVC (Switched Virtual Circuit)\n");
    printf("- CIR (Committed Information Rate)\n");
    printf("- DLCI (Data Link Connection Identifier)\n");
    
    printf("\nFrame Structure:\n");
    printf("- Flag: 1 byte\n");
    printf("- Address: 2-4 bytes\n");
    printf("- Data: up to 4096 bytes\n");
    printf("- FCS: 2 bytes\n");
    printf("- Flag: 1 byte\n");
    
    return 0;
}
