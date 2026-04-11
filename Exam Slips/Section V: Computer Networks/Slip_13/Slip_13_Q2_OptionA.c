/*
 * Slip 13 - Q2 Option A: Packet Analysis
 * 
 * Displays packet header information.
 * 
 * Compile: gcc Slip_13_Q2_OptionA.c -o packet
 * Run: ./packet
 */

#include <stdio.h>

typedef struct {
    unsigned char version_ihl;
    unsigned char type_service;
    unsigned short total_length;
    unsigned short identification;
} IPv4Header;

int main() {
    IPv4Header hdr = {0x45, 0x00, 0x3C, 0x1C};
    
    printf("IPv4 Header Analysis:\n");
    printf("Version: %d\n", hdr.version_ihl >> 4);
    printf("IHL: %d\n", hdr.version_ihl & 0x0F);
    printf("Type of Service: %d\n", hdr.type_service);
    printf("Total Length: %d bytes\n", hdr.total_length);
    printf("Identification: %d\n", hdr.identification);
    
    return 0;
}
