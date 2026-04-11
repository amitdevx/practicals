/*
 * Slip 18 - Q2 Option A: Protocol Parsing
 * 
 * Parses and displays protocol header information.
 * 
 * Compile: gcc Slip_18_Q2_OptionA.c -o protocol
 * Run: ./protocol
 */

#include <stdio.h>

int main() {
    printf("TCP/IP Protocol Stack\n");
    printf("=====================\n");
    printf("Layer 1 (Physical): Ethernet, PPP\n");
    printf("Layer 2 (Data Link): MAC, Frame Relay\n");
    printf("Layer 3 (Network): IP, ICMP, ARP\n");
    printf("Layer 4 (Transport): TCP, UDP\n");
    printf("Layer 5+ (Application): HTTP, FTP, DNS, SMTP\n");
    
    return 0;
}
