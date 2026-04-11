/*
 * Slip 18 - Q2 Option B: Packet Structure
 * 
 * Displays typical packet format and sizes.
 * 
 * Compile: gcc Slip_18_Q2_OptionB.c -o packet
 * Run: ./packet
 */

#include <stdio.h>

int main() {
    printf("UDP Packet Structure\n");
    printf("====================\n");
    printf("Source Port: 2 bytes\n");
    printf("Destination Port: 2 bytes\n");
    printf("Length: 2 bytes\n");
    printf("Checksum: 2 bytes\n");
    printf("Payload: variable\n");
    printf("\nTotal Header Size: 8 bytes\n");
    
    int src_port = 5000, dst_port = 53;
    int length = 100;
    
    printf("\nExample:\n");
    printf("SRC: %d  DST: %d  LEN: %d\n", src_port, dst_port, length);
    
    return 0;
}
