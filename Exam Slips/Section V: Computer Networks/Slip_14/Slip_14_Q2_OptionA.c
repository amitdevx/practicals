/*
 * Slip 14 - Q2 Option A: Baud Rate Calculator
 * 
 * Calculates data rate from baud rate and bits per symbol.
 * 
 * Compile: gcc Slip_14_Q2_OptionA.c -o baud
 * Run: ./baud
 */

#include <stdio.h>

int main() {
    double baud, bits_per_symbol;
    
    printf("Enter baud rate (bits/sec): ");
    scanf("%lf", &baud);
    printf("Enter bits per symbol: ");
    scanf("%lf", &bits_per_symbol);
    
    double data_rate = baud * bits_per_symbol;
    
    printf("Data rate: %.2lf bps\n", data_rate);
    printf("Kilobits/sec: %.2lf\n", data_rate / 1000);
    
    return 0;
}
