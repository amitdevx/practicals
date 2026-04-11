/*
 * Slip 2 - Q2 Option B (OR): Even Parity Error Detection
 * 
 * Detects single-bit errors using even parity.
 * 
 * Compile: gcc Slip_02_Q2_OptionB.c -o even_parity
 * Run: ./even_parity
 */

#include <stdio.h>

int main() {
    int data;
    
    printf("Even Parity Error Detection\n");
    printf("===========================\n");
    printf("Enter 7-bit data (0-127): ");
    scanf("%d", &data);
    
    if (data < 0 || data > 127) {
        printf("Invalid range\n");
        return 1;
    }
    
    int ones = 0;
    for (int i = 0; i < 7; i++) {
        if ((data >> i) & 1) ones++;
    }
    
    int parity = ones % 2;
    
    printf("Data: %d\n", data);
    printf("1-bits: %d\n", ones);
    printf("Parity bit: %d\n", parity);
    printf("Even parity: %s\n", parity == 0 ? "Yes" : "No");
    
    return 0;
}
