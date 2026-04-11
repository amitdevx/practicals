/*
 * Slip 16 - Q2 Option A: Hamming Code Error Correction
 * 
 * Detects and corrects single-bit errors.
 * 
 * Compile: gcc Slip_16_Q2_OptionA.c -o hamming
 * Run: ./hamming
 */

#include <stdio.h>

int main() {
    int data = 0x5;
    
    printf("Hamming (7,4) Code:\n");
    printf("==================\n");
    printf("Original data (4 bits): %d\n", data);
    
    int p1 = 0, p2 = 0, p4 = 0;
    for (int i = 1; i <= data; i = i << 1) {
        if (i & data) p1 ^= 1;
    }
    for (int i = 2; i <= data; i = i << 1) {
        if (i & data) p2 ^= 1;
    }
    for (int i = 4; i <= data; i = i << 1) {
        if (i & data) p4 ^= 1;
    }
    
    printf("Parity bits: p1=%d, p2=%d, p4=%d\n", p1, p2, p4);
    printf("Hamming code: %d%d%d%d\n", p4, p2, p1, data);
    
    return 0;
}
