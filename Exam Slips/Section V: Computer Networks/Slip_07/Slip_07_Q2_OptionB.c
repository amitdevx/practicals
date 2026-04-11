/*
 * Slip 7 - Q2 Option B (OR): Set up Dynamic Routing Protocols
 * 
 * Simulates RIP protocol configuration.
 * 
 * Compile: gcc Slip_07_Q2_OptionB.c -o routing
 * Run: ./routing
 */

#include <stdio.h>

int main() {
    printf("Dynamic Routing Protocols Configuration\n");
    printf("======================================\n\n");
    
    printf("RIP Configuration:\n");
    printf("─────────────────\n");
    printf("router rip\n");
    printf("version 2\n");
    printf("network 192.168.0.0\n");
    printf("network 10.0.0.0\n");
    printf("no auto-summary\n\n");
    
    printf("Routing Table:\n");
    printf("──────────────\n");
    printf("192.168.1.0/24 via 192.168.0.1\n");
    printf("10.0.0.0/8 via 10.0.0.254\n");
    printf("172.16.0.0/16 via 192.168.0.2\n");
    
    return 0;
}
