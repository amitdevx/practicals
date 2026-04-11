/*
 * Slip 9 - Q2 Option A: Even Parity Error Detection
 * 
 * Detects errors using even parity bit.
 * 
 * Compile: gcc Slip_09_Q2_OptionA.c -o even_parity
 * Run: ./even_parity
 */

#include <stdio.h>

int count_bits(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

int main() {
    int data;
    
    printf("Even Parity Error Detection\n");
    printf("============================\n");
    printf("Enter 7-bit data (0-127): ");
    scanf("%d", &data);
    
    if (data < 0 || data > 127) {
        printf("Invalid! Range is 0-127\n");
        return 1;
    }
    
    int ones = count_bits(data);
    int parity = ones % 2;
    int with_parity = (data << 1) | parity;
    
    printf("\nData: %d (binary: ", data);
    for (int i = 6; i >= 0; i--) {
        printf("%d", (data >> i) & 1);
    }
    printf(")\n");
    printf("Number of 1s: %d\n", ones);
    printf("Parity bit: %d\n", parity);
    printf("With parity: %d\n", with_parity);
    
    return 0;
}
