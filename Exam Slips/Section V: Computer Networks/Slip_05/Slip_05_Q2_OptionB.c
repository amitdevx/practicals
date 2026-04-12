/*
 * Slip 5 - Q2 Option B: Write a program to implement odd parity error detection.
 *
 * Compile: gcc Slip_05_Q2_OptionB.c -o odd_parity
 * Run: ./odd_parity
 */

#include <stdio.h>

int main(void) {
    char bits[128];
    int ones = 0;

    printf("Odd Parity Error Detection\n");
    printf("==========================\n");
    printf("Enter binary data: ");
    scanf("%127s", bits);

    for (int i = 0; bits[i] != '\0'; i++) {
        if (bits[i] == '1') {
            ones++;
        } else if (bits[i] != '0') {
            printf("Invalid input. Use only 0 and 1.\n");
            return 1;
        }
    }

    if (ones % 2 == 0) {
        printf("Parity bit for odd parity: 1\n");
    } else {
        printf("Parity bit for odd parity: 0\n");
    }

    printf("Total number of 1s after parity adjustment will be odd.\n");
    return 0;
}
