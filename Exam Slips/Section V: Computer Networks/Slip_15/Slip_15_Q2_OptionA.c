/*
 * Slip 15 - Q2 Option A: Modulation Schemes
 * 
 * Displays various modulation schemes and their efficiency.
 * 
 * Compile: gcc Slip_15_Q2_OptionA.c -o modulation
 * Run: ./modulation
 */

#include <stdio.h>

int main() {
    printf("Modulation Schemes:\n");
    printf("==================\n");
    printf("AM:  1 bit/Hz\n");
    printf("FM:  0.5 bits/Hz\n");
    printf("PSK: 2 bits/Hz\n");
    printf("QAM: 4 bits/Hz\n");
    printf("16-QAM: 4 bits/Hz\n");
    printf("64-QAM: 6 bits/Hz\n");
    
    return 0;
}
