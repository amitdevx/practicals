/*
 * Slip 4 - Q2 Option B (OR): Odd Parity Error Detection
 * 
 * Detects errors using odd parity.
 * 
 * Compile: gcc Slip_04_Q2_OptionB.c -o odd_parity
 * Run: ./odd_parity
 */

#include <stdio.h>

int main() {
    int data;
    
    printf("Odd Parity Error Detection\n");
    printf("==========================\n");
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
    printf("Odd parity: %s\n", parity == 1 ? "Yes" : "No");
    
    return 0;
}
