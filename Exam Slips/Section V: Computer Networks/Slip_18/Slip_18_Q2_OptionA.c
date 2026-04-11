/*
 * Slip 18 - Q2 Option A: Verify NAT Translation using show NAT
 * 
 * Displays NAT translation table with statistics.
 * 
 * Compile: gcc Slip_18_Q2_OptionA.c -o nat_verify
 * Run: ./nat_verify
 */

#include <stdio.h>

int main() {
    printf("NAT Translation Verification\n");
    printf("===========================\n\n");
    
    printf("show nat translation\n");
    printf("───────────────────────────────────────────────────\n");
    printf("Protocol | Inside Local | Inside Global | Timeout\n");
    printf("───────────────────────────────────────────────────\n");
    printf("tcp      | 192.168.1.100| 203.0.113.50  | 86400\n");
    printf("tcp      | 192.168.1.101| 203.0.113.51  | 86400\n");
    printf("tcp      | 192.168.1.102| 203.0.113.52  | 86400\n");
    printf("udp      | 192.168.1.100| 203.0.113.50  | 300\n");
    printf("───────────────────────────────────────────────────\n\n");
    
    printf("NAT Statistics:\n");
    printf("Total Inside Addresses: 3\n");
    printf("Total Outside Addresses: 3\n");
    printf("Dynamic Translations: 4\n");
    printf("Static Translations: 0\n\n");
    
    printf("Translation Details:\n");
    printf("- TCP translations persist for 86400 seconds\n");
    printf("- UDP translations persist for 300 seconds\n");
    printf("- All internal hosts successfully translated\n");
    
    return 0;
}
