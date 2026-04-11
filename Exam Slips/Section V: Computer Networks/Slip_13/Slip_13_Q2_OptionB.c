/*
 * Slip 13 - Q2 Option B: Network Sniffer
 * 
 * Simulates packet capture and analysis.
 * 
 * Compile: gcc Slip_13_Q2_OptionB.c -o sniffer
 * Run: ./sniffer
 */

#include <stdio.h>
#include <string.h>

int main() {
    printf("Network Sniffer\n");
    printf("===============\n");
    printf("Packet 1: SRC 192.168.1.100 -> DST 8.8.8.8 (DNS)\n");
    printf("Packet 2: SRC 10.0.0.50 -> DST 10.0.0.1 (HTTP)\n");
    printf("Packet 3: SRC 172.16.0.10 -> DST 172.16.0.5 (HTTPS)\n");
    
    return 0;
}
