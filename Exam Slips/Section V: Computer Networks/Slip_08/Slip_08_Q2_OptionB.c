/*
 * Slip 8 - Q2 Option B (OR): Static Routing Simulation
 * 
 * Simulates static route configuration.
 * 
 * Compile: gcc Slip_08_Q2_OptionB.c -o static_routing
 * Run: ./static_routing
 */

#include <stdio.h>

int main() {
    printf("Static Routing Simulation\n");
    printf("========================\n\n");
    
    printf("Static Routes Configured:\n");
    printf("─────────────────────────\n");
    printf("Route 192.168.1.0/24 via 10.0.0.1\n");
    printf("Route 172.16.0.0/16 via 10.0.0.2\n");
    printf("Route 0.0.0.0/0 via 10.0.0.254\n\n");
    
    printf("Routing Decision:\n");
    printf("Packet to 192.168.1.50 -> Forward to 10.0.0.1\n");
    printf("Packet to 172.16.5.10 -> Forward to 10.0.0.2\n");
    printf("Other packets -> Forward to 10.0.0.254\n");
    
    return 0;
}
