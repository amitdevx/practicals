/*
 * Slip 10 - Q2 Option A: Even Parity Error Detection
 *
 * Compile: gcc Slip_10_Q2_OptionA.c -o even_parity
 * Run: ./even_parity
 */

#include <stdio.h>
#include <string.h>

int is_binary(const char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != '0' && s[i] != '1') {
            return 0;
        }
    }
    return 1;
}

int count_ones(const char *s) {
    int c = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '1') {
            c++;
        }
    }
    return c;
}

int main(void) {
    char data[129];
    char received[130];

    printf("Even Parity Error Detection\n");
    printf("===========================\n");

    printf("Enter binary data bits (max 128 bits): ");
    scanf("%128s", data);

    if (!is_binary(data)) {
        printf("Invalid input: only 0 and 1 allowed.\n");
        return 1;
    }

    int ones = count_ones(data);
    int parity_bit = (ones % 2 == 0) ? 0 : 1;

    printf("\nData bits           : %s\n", data);
    printf("Count of 1s         : %d\n", ones);
    printf("Even parity bit     : %d\n", parity_bit);
    printf("Transmitted frame   : %s%d\n", data, parity_bit);

    printf("\nEnter received bits including parity: ");
    scanf("%129s", received);

    if (!is_binary(received)) {
        printf("Invalid input: only 0 and 1 allowed.\n");
        return 1;
    }

    int received_ones = count_ones(received);
    if (received_ones % 2 == 0) {
        printf("Result: NO ERROR (even number of 1s).\n");
    } else {
        printf("Result: ERROR DETECTED (odd number of 1s).\n");
    }

    return 0;
}
