/*
 * Slip 3 - Q2 Option B: Write a C program to implement even parity error detection.
 *
 * Compile: gcc Slip_03_Q2_OptionB.c -o parity
 * Run: ./parity
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char bits[128];
    int ones = 0;

    printf("Even Parity Error Detection\n");
    printf("===========================\n");
    printf("Enter binary data: ");
    scanf("%127s", bits);

    for (int i = 0; bits[i] != '\0'; i++) {
        if (bits[i] == '1') {
            ones++;
        } else if (bits[i] != '0') {
            printf("Invalid input. Only 0 and 1 are allowed.\n");
            return 1;
        }
    }

    printf("Number of 1s: %d\n", ones);
    if (ones % 2 == 0) {
        printf("Parity bit for even parity: 0\n");
        printf("Result: No error detected under even parity.\n");
    } else {
        printf("Parity bit for even parity: 1\n");
        printf("Result: Parity adjustment needed to maintain even parity.\n");
    }

    return 0;
}
