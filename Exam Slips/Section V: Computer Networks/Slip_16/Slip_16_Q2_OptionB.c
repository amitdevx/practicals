/*
 * Slip 16 - Q2 Option B: Cyclic Redundancy Check (CRC)
 * 
 * Calculates CRC for error detection.
 * 
 * Compile: gcc Slip_16_Q2_OptionB.c -o crc
 * Run: ./crc
 */

#include <stdio.h>
#include <string.h>

int main() {
    char data[100];
    int crc = 0;
    
    printf("Enter data: ");
    fgets(data, 100, stdin);
    data[strcspn(data, "\n")] = '\0';
    
    for (int i = 0; data[i]; i++) {
        crc = ((crc << 8) ^ data[i]) & 0xFFFF;
    }
    
    printf("Data: %s\n", data);
    printf("CRC-16: %04X\n", crc);
    
    return 0;
}
