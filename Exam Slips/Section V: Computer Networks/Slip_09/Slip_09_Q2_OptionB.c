/*
 * Slip 9 - Q2 Option B: Subnetting and Supernetting Calculations
 * 
 * Performs subnet and supernet calculations.
 * 
 * Compile: gcc Slip_09_Q2_OptionB.c -o subnetting
 * Run: ./subnetting
 */

#include <stdio.h>

int main() {
    printf("Subnetting and Supernetting\n");
    printf("===========================\n\n");
    
    printf("Example: 192.168.10.0/25\n");
    int prefix = 25;
    int host_bits = 32 - prefix;
    int hosts = (1 << host_bits) - 2;
    
    printf("Network bits: %d\n", prefix);
    printf("Host bits: %d\n", host_bits);
    printf("Subnet mask: 255.255.255.128\n");
    printf("Usable hosts: %d\n", hosts);
    printf("Broadcast: 192.168.10.255\n\n");
    
    printf("Supernetting example:\n");
    printf("Combining 4x /26 networks into /24\n");
    printf("192.168.10.0/26 + 192.168.10.64/26 +\n");
    printf("192.168.10.128/26 + 192.168.10.192/26\n");
    printf("= 192.168.10.0/24\n");
    
    return 0;
}
